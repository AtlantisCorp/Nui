/**
 * @file NTabView.cpp
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-27
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "Nui/NTabView.h"

namespace Nui
{
    class TabViewBarScroll : public ScrollView
    {
        Orientation mOrientation;
        
    public:
        
        Size intrinsicContentSize() const
        {
            auto p = parentView();
            auto content = contentView();
            Size size = ScrollView::intrinsicContentSize();
            
            if (p) {
                if (mOrientation == Orientation::Horizontal) {
                    size.width = p->intrinsicContentSize().width;
                }
                else {
                    size.height = p->intrinsicContentSize().height;
                }
            }
            if (content) {
                if (mOrientation == Orientation::Horizontal) {
                    size.height = content->intrinsicContentSize().height;
                }
                else {
                    size.width = content->intrinsicContentSize().width;
                }
            }
            
            return size;
        }
    };
    
    class TabViewContentScroll : public ScrollView
    {
    public:
        Size intrinsicContentSize() const
        {
            auto p = std::dynamic_pointer_cast < TabView >(parentView());
            auto bar = p->bar();
            
            if (p && bar) {
                 if (bar->orientation() == Orientation::Horizontal) {
                     return Size{
                         p->intrinsicContentSize().width,
                         p->intrinsicContentSize().height - bar->intrinsicContentSize().height
                     };
                 }
                else {
                    return Size {
                        p->intrinsicContentSize().width - bar->intrinsicContentSize().width,
                        p->intrinsicContentSize().height
                    };
                }
            }
            
            return ScrollView::intrinsicContentSize();
        }
    };
    
    TabView::TabView(Orientation orientation, Alignment alignment)
    {
        mTabBar = Make < TabBar >();
        mTabBar->setOrientation(orientation);
        mTabBar->setAlignment(alignment);
        
        mTabBarScrollView = Make < TabViewBarScroll >();
        mTabBarScrollView->setContentView(mTabBar);
        
        mContentViewScroll = Make < TabViewContentScroll >();
    }
    
    void TabView::layoutChildren()
    {
        if (mTabBar->orientation() == Orientation::Horizontal) {
            mTabBarScrollView->setFrameOrigin({ 0, 0 });
            mContentViewScroll->setFrameOrigin({ 0, mTabBar->frame().size.height });
        }
        else {
            mTabBarScrollView->setFrame({ 0, 0 });
            mContentViewScroll->setFrameOrigin({ mTabBar->frame().size.width, 0 });
        }
    }
    
    Shared < View > TabView::contentView() const
    {
        if (!mContentViewScroll) {
            return nullptr;
        }
        return mContentViewScroll->contentView();
    }
    
    ssize_t TabView::selectedIndex() const
    {
        if (!mTabBar) {
            return -1;
        }
        return mTabBar->selectedIndex();
    }
    
    void TabView::attached()
    {
        addChildren(mTabBarScrollView, mContentViewScroll);
    }
}
