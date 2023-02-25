/**
 * @file NFont.mm
 * @author Luk2010
 * @brief
 * @version 0.1
 * @date 2023-02-24
 *
 * @copyright Atlanti's Corp @2023
 *
 */

#include "Nui/NFont.h"

Nui::Font::Font(std::string_view name, double size)
{
    mHandle = [NSFont fontWithName:@(name.data()) size:size];
}
