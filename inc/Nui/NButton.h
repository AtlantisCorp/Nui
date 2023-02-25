/**
 * @file NButton.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_BUTTON_H__
#define __NUI_BUTTON_H__

#include "NTextControl.h"
#include "NButtonType.h"

namespace Nui 
{
    /**
     * @brief A native button that can be customized.
     * 
     */
    class Button : public TextControl  
    {
        //! @brief The button's type.
        ButtonType mButtonType;
        
        //! @brief The alternate text color.
        Color mAlternateTextColor;
        
        //! @brief The alternate text.
        std::string mAlternateText;

    public:
        //! @brief Creates a new Button.
        Button(std::string_view title, const std::function < void(TextControl const&) >& handler = {});

        //! @brief Sets the button type.
        virtual void setButtonType(ButtonType type);

        //! @brief Returns the button type.
        inline ButtonType buttonType() const { return mButtonType; }
        
        //! @brief Sets the text color.
        virtual void setTextColor(const Color& color);
        
        //! @brief Sets the alternate text color.
        virtual void setAlternateTextColor(const Color& color);
        
        //! @brief Returns the alternate text color.
        inline const Color& alternateTextColor() const { return mAlternateTextColor; }
        
        //! @brief Sets the alternate text.
        virtual void setAlternateText(std::string_view text);
        
        //! @brief Returns the alternate text.
        inline const std::string& alternateText() const { return mAlternateText; }
    };
}

#endif 
