/**
 * @file NTextEdit.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_TEXTEDIT_H__
#define __NUI_TEXTEDIT_H__

#include "NTextControl.h"

namespace Nui
{
    /**
     *  @brief A text input control.
     *
     */
    class TextEdit : public TextControl
    {
        //! @brief The placeholder string.
        std::string mPlaceholder;

    protected:

#       if NUI_PLATFORM_APPLE

        //! @brief Constructs a TextEdit from a NSTextField.
        inline TextEdit(NUI_OBJC_HDL(NSTextField) handle): TextControl(handle) {}

#       endif 
        
    public:
        //! @brief Creates a new TextEdit.
        TextEdit(std::string_view text = "");
        
        //! @brief Sets a placeholder string.
        virtual void setPlaceholder(std::string_view placeholder);
        
        //! @brief Returns the placeholder string.
        const std::string& placeholder() const { return mPlaceholder; }
    };
}

#endif
