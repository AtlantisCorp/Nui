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
#include "NImage.h"

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
        
        //! @brief The button's image.
        Shared < Image > mImage;
        
        //! @brief The horizontal padding.
        double mHorizontalPadding;
        
        //! @brief The vertical padding.
        double mVerticalPadding;

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
        
        //! @brief Sets the button's image.
        virtual void setImage(const Shared < Image >& image);
        
        //! @brief Returns the button's image.
        inline Shared < Image > image() const { return mImage; }
        
        //! @brief Sets the horizontal padding.
        virtual void setHorizontalPadding(double value);
        
        //! @brief Returns the horizontal padding.
        inline double horizontalPadding() const { return mHorizontalPadding; }
        
        //! @brief Sets the vertical padding.
        virtual void setVerticalPadding(double value);
        
        //! @brief Returns the vertical padding.
        inline double verticalPadding() const { return mVerticalPadding; }
    };
}

#endif 
