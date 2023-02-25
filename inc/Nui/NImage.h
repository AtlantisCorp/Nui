/**
 * @file NImage.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-25
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_IMAGE_H__
#define __NUI_IMAGE_H__

#include "NPlatform.h"

namespace Nui
{
    /**
     * @brief An interface for native image loading.
     * 
     */
    class Image 
    {
#       if NUI_PLATFORM_APPLE 

        //! @brief The NSImage handle.
        NUI_OBJC_HDL(NSImage) mHandle;

#       endif 

        //! @brief The image file path.
        fs::path mFilePath;

    public: 

        //! @brief Creates a new Image and loads a file.
        Image(const fs::path& filepath);

#       if NUI_PLATFORM_APPLE

        //! @brief Returns the NSImage handle.
        inline NUI_OBJC_HDL(NSImage) handle() const { return mHandle; }

#       endif
    };
}

#endif 