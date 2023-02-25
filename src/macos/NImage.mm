/**
 * @file NImage.mm
 * @author Luk2010
 * @brief
 * @version 0.1
 * @date 2023-02-25
 *
 * @copyright Atlanti's Corp @2023
 *
 */

#include "Nui/NImage.h"

Nui::Image::Image(const fs::path& filepath)
{
    mHandle = [[NSImage alloc] initWithContentsOfFile:@(filepath.string().data())];
    if (!mHandle) {
        throw std::runtime_error("Nui:Image: Cannot open image file '"s + filepath.string() + "'.");
    }
}
