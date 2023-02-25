/**
 * @file NButtonType.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-25
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_BUTTONTYPE_H__
#define __NUI_BUTTONTYPE_H__

#include "NPlatform.h"

namespace Nui 
{
    /**
     * @brief Enumerates available Button types.
     * 
     */
    enum class ButtonType 
    {
        //! @brief A custom button that doesn't have the native style.
        Custom,

        //! @brief A standard button that can have an alternate title and image. Uses this button for 
        //! natives look default buttons.
        MomentaryPushIn,

        //! @brief A button that sticks to its on state when pushed in.
        PushOnPushOff,

        //! @brief A native radio button.
        Radio,

        //! @brief A native checkbox.
        CheckBox,

        //! @brief A button that sends repeating actions as pressure changes occur.
        Accelerator,

        //! @brief A button that allows for a configurable number of stepped pressure levels and provides
        //! tactile feedback as the user reaches each step.
        MultiLevelAccelerator
    };
}

#endif 