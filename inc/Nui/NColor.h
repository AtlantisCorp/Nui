/**
 * @file NColor.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-23
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_COLOR_H__
#define __NUI_COLOR_H__

#include "NPlatform.h"

namespace Nui 
{
    /**
     * @brief A RGBA color.
     * 
     */
    struct Color 
    {
        double red = .0;
        double green = .0;
        double blue = .0;
        double alpha = 1.;
    };
}

#endif // !__NUI_COLOR_H__