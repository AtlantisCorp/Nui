/**
 * @file NWindowStyle.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-23
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_WINDOWSTYLE_H__
#define __NUI_WINDOWSTYLE_H__

#include "NPlatform.h"

namespace Nui 
{
    /**
     * @brief The different styles available for a Window.
     * 
     */
    struct WindowStyle 
    {
        bool closable:1 = true;
        bool resizable:1 = true;
        bool titled:1 = true; 
    };
}

#endif // !__NUI_WINDOWSTYLE_H__
