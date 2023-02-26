/**
 * @file NTabBar.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_TABBAR_H__
#define __NUI_TABBAR_H__

#include "NView.h"
#include "NTabBarItem.h"

namespace Nui 
{
    /**
     * @brief A bar that can be displayed horizontally or vertically to show custom buttons 
     *        for a TabView. 
     * 
     * You can create a TabView and it will generate the TabBar for you. If you want to display
     * document based views, use DocumentTabView which will associate a TabBar item index with 
     * a document. 
     * 
     * When user clicks on a TabBarItem, the TabBarItem calls the TabView's method selectIndex()
     * with the item index.
     * 
     */
    class TabBar : public View 
    {
        friend class TabBarItem;

        //! @brief The list of TabBarItems to display.
        std::vector < Shared < TabBarItem > > mItems; 

        //! @brief The currently selected item.
        ssize_t mSelectedIndex;

    public:

        //! @brief Selects the given item index.
        virtual void selectIndex(ssize_t index);

        //! @brief Returns the selected index.
        virtual ssize_t selectedIndex(void) const; 

        //! @brief Returns the selected item.
        virtual Shared < TabBarItem > selectedItem(void) const;
    };
}

#endif 