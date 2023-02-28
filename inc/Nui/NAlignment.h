/**
 * @file NAlignment.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_ALIGNMENT_H__
#define __NUI_ALIGNMENT_H__

#include "NPlatform.h"

namespace Nui 
{
    /**
     * @brief The standard alignment values.
     * 
     */
    enum class Alignment 
    {
        Left, 
        Center, 
        Right,
        Top = Left,
        Bottom = Right
    };
}

#endif 