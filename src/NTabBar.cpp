/**
 * @file NTabBar.cpp
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "Nui/NTabBar.h"
#include "Nui/NTabView.h"

namespace Nui 
{
    void TabBar::selectIndex(size_t index)
    {
        if (index >= mItems.size()) {
            std::cerr << "Nui:TabBar: Trying to select item index " << index << ", which is invalid." << std::endl;
            return;
        }
        if (mSelectedIndex >= 0) {
            auto selItem = mItems.at(mSelectedIndex);
            if (selItem) {
                selItem->setDefaultState(ViewState::Neutral);
            }
        }
        auto item = mItems.at(index);
        item->setDefaultState(ViewState::Hovered);
        mSelectedIndex = static_cast < ssize_t >(index);
        onItemSelected(index);
        if (mTabView) {
            mTabView->onSelectedIndex(index);
        }
    }

    Shared < TabBarItem > TabBar::selectedItem() const 
    {
        if (mSelectedIndex > -1) {
            return mItems.at(mSelectedIndex);
        }
        return nullptr;
    }

    void TabBar::insertItem(size_t index, const Shared < TabBarItem >& item)
    {
        if (!item) {
            throw std::runtime_error("Nui:TabBar: Cannot insert null TabBarItem.");
        }

        auto it = mItems.begin();
        std::advance(it, index);
        it = mItems.insert(it, item);

        item->mTabBar = this; 

        while (it != mItems.end()) {
            (*it)->mIndex = static_cast < ssize_t >(std::distance(mItems.begin(), it));
        }

        addChild(item);
        updateLayout();
    }

    void TabBar::removeItem(size_t index) 
    {
        if (index >= mItems.size()) {
            std::cerr << "Nui:TabBar: Trying to remove index " << index << ", which is invalid." << std::endl;
            return;
        }
        auto item = mItems.at(index);
        item->mTabBar = NULL; 
        item->mIndex = -1;
        auto it = mItems.begin();
        std::advance(it, index);
        mItems.erase(it);
        removeChild(item);
        updateLayout();
    }

    size_t TabBar::numberOfItems() const 
    {
        return mItems.size();
    }

    Size TabBar::intrinsicContentSize() const
    {
        Size neededSize = { .0, .0 };
        for (auto item : mItems) {
            Size itemSize = item->intrinsicContentSize();
            neededSize.width += itemSize.width;
            neededSize.height = std::max(neededSize.height, itemSize.height);
        }
        return neededSize;
    }

    void TabBar::layoutChildren() 
    {
        Point currCoords = { .0, .0 };

        if (mOrientation == Orientation::Horizontal) {
            if (mAlignment == Alignment::Left) {
                for (auto item : mItems) {
                    item->setFrameOrigin(currCoords);
                    currCoords.x += item->intrinsicContentSize().width;
                }
            }
            else if (mAlignment == Alignment::Right) {
                currCoords.x = intrinsicContentSize().width;
                for (auto it = mItems.rbegin(); it != mItems.rend(); ++it) {
                    currCoords.x -= (*it)->intrinsicContentSize().width;
                    (*it)->setFrameOrigin(currCoords);
                }
            }
            else if (mAlignment == Alignment::Center) {
                Size neededSize = { .0, .0 };
                for (auto item : mItems) {
                    neededSize.width += item->intrinsicContentSize().width;
                }
                currCoords.x = intrinsicContentSize().width - (neededSize.width / 2);
                for (auto item : mItems) {
                    item->setFrameOrigin(currCoords);
                    currCoords.x += item->intrinsicContentSize().width;
                }
            }
        }
    }
}