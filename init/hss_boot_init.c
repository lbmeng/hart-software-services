/*******************************************************************************
 * Copyright 2019 Microchip Corporation.
 *
 * SPDX-License-Identifier: MIT
 * 
 * MPFS HSS Embedded Software
 *
 */

/**
 * \file HSS Boot Initalization
 * \brief Boot Initialization
 */

#include "config.h"
#include "hss_types.h"

#ifdef CONFIG_SERVICE_BOOT
#  include "hss_boot_service.h"
#endif
#  include "hss_sys_setup.h"

#ifdef CONFIG_SERVICE_OPENSBI
#  include "opensbi_service.h"
#endif

#ifdef CONFIG_SERVICE_QSPI
//#  include "encoding.h"
#  include "qspi_service.h"
//#  include <mss_qspi.h>
#endif

#ifdef CONFIG_SERVICE_EMMC
#  include "emmc_service.h"
#endif

#include "hss_state_machine.h"
#include "hss_debug.h"
#include "hss_crc32.h"

#include <string.h>
#include <assert.h>

#ifdef CONFIG_COMPRESSION
#  include "hss_decompress.h"
#endif

#include "hss_memcpy_via_pdma.h"
#include "hss_boot_pmp.h"

static bool validateCrc_(struct HSS_BootImage *pImage)
{
    bool result = false;
    uint32_t headerCrc, originalCrc;
    struct HSS_BootImage header = *pImage;

    originalCrc = header.headerCrc;
    header.headerCrc = 0u;

    headerCrc = CRC32_calculate((const uint8_t *)&header, sizeof(struct HSS_BootImage)); 

    if (headerCrc == originalCrc) {
        result = true;
    }

    return result;
}

bool HSS_BootInit(void)
{
    bool result = false;

    mHSS_DEBUG_PRINTF("Initializing Boot Image.." CRLF);

#ifdef CONFIG_SERVICE_BOOT
#  if (defined(CONFIG_SERVICE_QSPI) || defined(CONFIG_SERVICE_EMMC))
    struct HSS_BootImage *pBootImage = NULL;
#  elif defined(CONFIG_SERVICE_BOOT_USE_PAYLOAD)
    // assuming that boot image is statically linked with the HSS ELF
    //
    extern const char _payload_start;
    struct HSS_BootImage *pBootImage = (struct HSS_BootImage *)&_payload_start;
    //mHSS_DEBUG_PRINTF("pBootImage is %p, magic is %x" CRLF, pBootImage, pBootImage->magic);
#  else
#      error Unable to determine boot mechanism
#  endif

#  if defined(CONFIG_COMPRESSION)
     // for now, compression only works with payload
     (!pBootImage) {
        mHSS_DEBUG_PRINTF("Boot Image NULL, ignoring" CRLF);
        result = false;
     } else {
        mHSS_DEBUG_PRINTF("Preparing to decompress to DDR..." CRLF);
        void* const pInput = (void*)pBootImage;
        void * const pOutputInDDR = (void *)(CONFIG_SERVICE_BOOT_DDR_TARGET_ADDR);

        int outputSize = HSS_Decompress(pInput, pOutputInDDR);
        mHSS_DEBUG_PRINTF("decompressed %d bytes..." CRLF, outputSize);

        if (outputSize) {
            pBootImage = (struct HSS_BootImage *)pOutputInDDR;
        } else {
            pBootImage = NULL;
        }
#  elif defined(CONFIG_SERVICE_EMMC) || defined(CONFIG_SERVICE_QSPI)
     {
#    ifndef CONFIG_SERVICE_QSPI_COPY_TO_DDR
         // TODO: refactor
#        error SERVICE_QSPI_COPY_TO_DDR must be set
#    endif

#    if defined(CONFIG_SERVICE_EMMC)
        mHSS_DEBUG_PRINTF("Preparing to copy from EMMC to DDR..." CRLF);
#    elif defined (CONFIG_SERVICE_QSPI)
        mHSS_DEBUG_PRINTF("Preparing to copy from QSPI to DDR..." CRLF);
#    endif
        // set pDestImageInDDR to an appropriate location in DDR
        void *pDestImageInDDR = (void *)(CONFIG_SERVICE_BOOT_DDR_TARGET_ADDR);

#    if (defined(CONFIG_SERVICE_QSPI) && !defined(CONFIG_SERVICE_QSPI_USE_XIP))
        // if we are not using XIP, then we need to do an initial copy of the
        // boot header into our structure, for subsequent use
        struct HSS_BootImage bootImage;
    	HSS_QSPI_MemCopy(&bootImage, (void *)0, sizeof(struct HSS_BootImage));
        pBootImage = &bootImage;
#    elif defined(CONFIG_SERVICE_EMMC)
        // if we are using EMMC, then we also need to do an initial copy of the
        // boot header into our structure, for subsequent use
        struct HSS_BootImage bootImage;
    	HSS_EMMC_MemCopy(&bootImage, (void *)0, sizeof(struct HSS_BootImage));
        pBootImage = &bootImage;
#    endif

        // quickly validate boot image header before a needless copy is performed
        if (pBootImage->magic == mHSS_BOOT_MAGIC) { // causes problems w. RENODE
            mHSS_DEBUG_PRINTF("Copying %lu bytes to 0x%X" CRLF, 
                pBootImage->bootImageLength, pDestImageInDDR);

            const size_t maxChunkSize = 4096u * 256u;
            size_t bytesLeft = pBootImage->bootImageLength;
            size_t chunkSize = mMIN(pBootImage->bootImageLength, maxChunkSize);
            char *pSrc = (char *)0;
            char *pDest = pDestImageInDDR;

            const char throbber[] = { '|', '/', '-', '\\' };
            unsigned int state = 0u;
            while (bytesLeft) {
                state++; state %= 4;
                mHSS_DEBUG_PRINTF_EX("%c %lu bytes (%lu remain) to 0x%X\r", 
                    throbber[state], chunkSize, bytesLeft, pDest);

#    if defined(CONFIG_SERVICE_EMMC)
    	        HSS_EMMC_MemCopy(pDest, pSrc, chunkSize);
#    else
    	        HSS_QSPI_MemCopy(pDest, pSrc, chunkSize);
#    endif

                pSrc += chunkSize;
                pDest += chunkSize;
                bytesLeft -= chunkSize;

                chunkSize = mMIN(bytesLeft, maxChunkSize);
            }

            // clear copy output to console by printing an empty string
            mHSS_DEBUG_PRINTF_EX("                                                                      \r");

            pBootImage = (struct HSS_BootImage *)pDestImageInDDR;
        }
#  endif

        if (!pBootImage) {
            mHSS_DEBUG_PRINTF("Boot Image NULL, ignoring" CRLF);
            result = false;
        } else if (validateCrc_(pBootImage)) {
            mHSS_DEBUG_PRINTF("decompressed boot image passed CRC" CRLF);

        // GCC 9.x appears to dislike the pBootImage cast, and sees dereferincing the set name as
        // an out-of-bounds... So we'll disable that warning just for this print...
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
            mHSS_DEBUG_PRINTF("Boot image set name: \"%s\"" CRLF, pBootImage->set_name);
#pragma GCC diagnostic pop
            HSS_Register_Boot_Image(pBootImage); 
            mHSS_DEBUG_PRINTF("Boot Image registered..." CRLF);

            if (HSS_Boot_RestartCore(HSS_HART_ALL) == IPI_SUCCESS) {
                result = true;
	    } else {
                result = false;
	    }
        } else {
            mHSS_DEBUG_PRINTF("decompressed boot image failed CRC" CRLF);
        }
    }
#endif

    return result;
}
