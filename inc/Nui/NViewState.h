/**
 * @file NViewState.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_VIEWSTATE_H__
#define __NUI_VIEWSTATE_H__

#include "NPlatform.h" 

namespace Nui 
{
    /**
     * @brief The available states for a View.
     * 
     */
    enum class ViewState 
    {
        //! @brief The default state.
        Neutral,

        //! @brief The view is currently hovered by the mouse.
        Hovered,

        //! @brief The view is currently clicked down by the mouse.
        Clicked
    };
}

#endif 