/**
 * @file NSize.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-23
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_SIZE_H__
#define __NUI_SIZE_H__

#include "NPlatform.h"

namespace Nui 
{
    /**
     * @brief A 2D size.
     * 
     */
    struct Size 
    {
        double width = .0;
        double height = .0;
    };
}

#endif // !__NUI_SIZE_H__