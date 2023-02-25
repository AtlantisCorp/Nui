/**
 * @file NLabel.mm
 * @author Luk2010
 * @brief
 * @version 0.1
 * @date 2023-02-23
 *
 * @copyright Atlanti's Corp @2023
 *
 */

#include "Nui/NLabel.h"

Nui::Label::Label(const std::string& text):
Nui::TextControl([NSTextField labelWithString:@(text.data())])
{
    setText(text);
    ((NSTextField*)handle()).bezeled = NO;
}
