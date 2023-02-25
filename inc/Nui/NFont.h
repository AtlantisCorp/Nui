/**
 * @file NFont.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_FONT_H__
#define __NUI_FONT_H__

#include "NPlatform.h"

namespace Nui 
{
    /**
     * @brief A text font.
     * 
     */
    class Font 
    {
#       if NUI_PLATFORM_APPLE

        //! @brief The font handle.
        NUI_OBJC_HDL(NSFont) mHandle;

    public: 

        //! @brief Returns the font handle.
        inline NUI_OBJC_HDL(NSFont) handle() const { return mHandle; }

#       endif 

    public: 
        //! @brief Creates a new font.
        Font(std::string_view name, double size);
    };
}

#endif // !__NUI_FONT_H__