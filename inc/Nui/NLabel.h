/**
 * @file NLabel.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-23
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_LABEL_H__
#define __NUI_LABEL_H__

#include "NTextControl.h"

namespace Nui
{
    /**
     * @brief A label that displays a text.
     * 
     */
    class Label : public TextControl
    {
    public:
        //! @brief Creates a new Label.
        Label(const std::string& text = "");
    };
}

#endif // !__NUI_LABEL_H__
