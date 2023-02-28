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
#include "NAlignment.h"
#include "NOrientation.h"

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
        friend class TabView;

        //! @brief The TabView that owns this TabBar.
        class TabView* mTabView;

        //! @brief The list of TabBarItems to display.
        std::vector < Shared < TabBarItem > > mItems; 

        //! @brief The currently selected item.
        ssize_t mSelectedIndex = -1;

        //! @brief The current TabBar orientation.
        Orientation mOrientation = Orientation::Horizontal;

        //! @brief The current TabBar alignment.
        Alignment mAlignment = Alignment::Left;

    public:

        //! @brief Selects the given item index.
        virtual void selectIndex(size_t index);

        //! @brief Returns the selected index.
        virtual inline ssize_t selectedIndex(void) const { return mSelectedIndex; }

        //! @brief Returns the selected item.
        virtual Shared < TabBarItem > selectedItem(void) const;

        //! @brief Inserts a new TabBarItem at the given index.
        virtual void insertItem(size_t index, const Shared < TabBarItem >& item);

        //! @brief Removes the item at given index.
        virtual void removeItem(size_t index);

        //! @brief Returns the current number of items.
        virtual size_t numberOfItems(void) const; 

        //! @brief Appends an item. 
        inline void appendItem(const Shared < TabBarItem >& item)
        {
            insertItem(numberOfItems(), item);
        }

        //! @brief Prepends an item.
        inline void prependItem(const Shared < TabBarItem >& item) 
        {
            insertItem(0, item);
        }

        //! @brief Returns the default intrinsic size for a TabBar, which is the sum of the
        //! TabBarItem widthes for a Horizontal TabBar, and the sum of the TabBarItem heightes
        //! for a Vertical TabBar.
        Size intrinsicContentSize(void) const;

        //! @brief Layouts its children. If the TabBar is horizontal, the children are 
        //! aligned in Left, Center or Right mode. If the TabBar is vertical, the children
        //! are aligned in Top, Center or Bottom mode.
        void layoutChildren(void);
        
        //! @brief Sets the TabBar orientation.
        inline void setOrientation(Orientation value) { mOrientation = value; }
        
        //! @brief Returns the TabBar orientation.
        inline Orientation orientation() const { return mOrientation; }
        
        //! @brief Sets the TabBar alignment.
        inline void setAlignment(Alignment value) { mAlignment = value; }
        
        //! @brief Returns the TabBar alignment.
        inline Alignment alignment() const { return mAlignment; }

    NUI_EVENT:

        //! @brief An item has been selected:
        virtual void onItemSelected(size_t index) {}
    };
}

#endif 
