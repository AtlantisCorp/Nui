/**
 * @file NTextEdit.mm
 * @author Luk2010
 * @brief
 * @version 0.1
 * @date 2023-02-24
 *
 * @copyright Atlanti's Corp @2023
 *
 */

#include "Nui/NTextEdit.h"

Nui::TextEdit::TextEdit(std::string_view text):
TextControl([NSTextField textFieldWithString:@""])
{
    setText((std::string)text);
}

void Nui::TextEdit::setPlaceholder(std::string_view placeholder)
{
    mPlaceholder = placeholder;
    ((NSTextField*)handle()).placeholderString = @(placeholder.data());
}
