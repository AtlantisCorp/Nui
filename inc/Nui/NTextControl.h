/**
 * @file NTextControl.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_TEXTCONTROL_H__
#define __NUI_TEXTCONTROL_H__

#include "NView.h"
#include "NFont.h"
#include "NTextAlign.h"

namespace Nui 
{
    /**
     * @brief A base class for all NView that manages a text.
     * 
     */
    class TextControl : public View  
    {
        //! @brief The text to display.
        std::string mText;

        //! @brief The font to display.
        Shared < Font > mFont; 

        //! @brief The text color.
        Color mTextColor;

        //! @brief The text alignment.
        TextAlign mTextAlign;

        //! @brief A function to call if set, when the button is clicked on (or entered).
        std::function < void(TextControl const&) > mActionPfn;
        
#       if NUI_PLATFORM_APPLE
        
        //! @brief The action handler.
        id mPfnHandler;
        
#       endif

    protected:

#       if NUI_PLATFORM_APPLE
        
        //! @brief Constructor.
        TextControl(NUI_OBJC_HDL(NSControl) handle);
        
#       endif

    public:

        //! @brief Returns the label's text.
        virtual inline const std::string& text() const { return mText; }

        //! @brief Sets the current text.
        virtual void setText(const std::string& text);
        
        //! @brief Returns the text font.
        virtual inline Shared < Font > font() const { return mFont; }
        
        //! @brief Sets the text font.
        virtual void setFont(const Shared < Font >& font);
        
        //! @brief Returns the text color.
        virtual inline const Color& textColor() const { return mTextColor; }
        
        //! @brief Sets the text color.
        virtual void setTextColor(const Color& color);
        
        //! @brief Returns the size that fits the control with the current configuration.
        virtual Size preferredSize() const; 

        //! @brief Sets the text alignment.
        virtual void setTextAlign(TextAlign value);

        //! @brief Returns the text alignment.
        virtual inline TextAlign textAlign() const { return mTextAlign; }

        //! @brief Sets the action handler for the Button.
        virtual inline void setActionHandler(const std::function < void(TextControl const&) >& handler) 
        {
            mActionPfn = handler;
        }

    NUI_EVENT:

        //! @brief Called when the button is clicked or entered.
        virtual inline void action(void) 
        {
            if (mActionPfn) {
                mActionPfn(*this);
            }
        }
    };
}

#endif 
