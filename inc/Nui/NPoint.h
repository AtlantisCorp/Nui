/**
 * @file NPoint.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-23
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_POINT_H__
#define __NUI_POINT_H__

#include "NPlatform.h"

namespace Nui 
{
    /**
     * @brief A 2D point.
     * 
     */
    struct Point 
    {
        double x = .0;
        double y = .0;
    };
}

#endif // !__NUI_POINT_H__