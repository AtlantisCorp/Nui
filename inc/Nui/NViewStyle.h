/**
 * @file NViewStyle.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_VIEWSTYLE_H__
#define __NUI_VIEWSTYLE_H__

#include "NPlatform.h"
#include "NColor.h"
#include "NFont.h"
#include "NTextAlign.h"

namespace Nui 
{
    /**
     * @brief Resumes the styles that can be applied to a view.
     * 
     * You can define a style and use it with View::setStyle(state, style). The view will update its
     * style by calling the updateStyle() method. This method may be overriden by subclasses like 
     * TextControl or Button. 
     * 
     */
    struct ViewStyle 
    {
        //! @brief The backgroud color.
        std::optional < Color > backgroundColor;

        //! @brief The border color.
        std::optional < Color > borderColor;

        //! @brief The border width.
        std::optional < double > borderWidth;

        //! @brief The corner radius.
        std::optional < double > cornerRadius;

        //! @brief The text color.
        std::optional < Color > textColor;

        //! @brief The text font.
        std::optional < Shared < Font > > font;
        
        //! @brief The text alignment.
        std::optional < TextAlign > textAlign;
    };
}

#endif 
