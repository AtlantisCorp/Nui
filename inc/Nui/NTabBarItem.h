/**
 * @file NTabBarItem.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_TABBARITEM_H__
#define __NUI_TABBARITEM_H__

#include "NView.h"
#include "NButton.h"

namespace Nui 
{
    /**
     * @brief An item in a TabBar. 
     * 
     * The item is a Button which responds to mouseDown events. The item has a TabBar registered 
     * which can be called whenever the item needs it.
     * Fields mIndex and mTabBar are updated by the TabBar itself.
     * 
     */
    class TabBarItem : public Button 
    {
        friend class TabBar; 

        //! @brief The TabBar that owns this item.
        class TabBar* mTabBar = NULL; 

        //! @brief The item's index.
        ssize_t mIndex = -1; 

    public: 

        //! @brief Creates a default TabBarItem.
        TabBarItem(std::string_view title, std::string_view icon = "");

        //! @brief Returns the TabBar for this item.
        inline TabBar* bar() { return mTabBar; }

        //! @brief Returns the TabBar for this item.
        inline const TabBar* bar() const { return mTabBar; }

        //! @brief Returns the item's index.
        inline ssize_t index() const { return mIndex; }

    NUI_EVENT: 

        //! @brief The item is clicked on and should be selected.
        virtual void action(void);
    };
}

#endif 