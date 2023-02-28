/**
 * @file NTabBarItem.cpp
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-27
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "Nui/NTabBarItem.h"
#include "Nui/NTabBar.h"

Nui::TabBarItem::TabBarItem(std::string_view title, std::string_view icon):
Nui::Button(title)
{
    if (!icon.empty()) {
        auto image = Make < Image >(icon);
        if (image) {
            setImage(image);
        }
    }
    setStyle(ViewState::Neutral, ViewStyle{
        .backgroundColor = Color{ .9, .9, .9 },
        .textAlign = TextAlign::Center,
        .textColor = Color{ .0, .0, .0 }
    });
    setStyle(ViewState::Hovered, ViewStyle{
        .backgroundColor = Color{ .8, .8, .8 }
    });
    setStyle(ViewState::Clicked, ViewStyle{
        .backgroundColor = Color{ .7, .7, .7 }
    });
}

void Nui::TabBarItem::action()
{
    if (mTabBar && mIndex > -1) {
        mTabBar->selectIndex(static_cast < size_t >(mIndex));
    }
    Button::action();
}
