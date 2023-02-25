/**
 * @file NRect.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-23
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_RECT_H__
#define __NUI_RECT_H__

#include "NPoint.h"
#include "NSize.h"

namespace Nui 
{
    /**
     * @brief A 2D rectangle.
     * 
     */
    struct Rect 
    {
        Point origin;
        Size size;
    };
}

#endif // !__NUI_RECT_H__