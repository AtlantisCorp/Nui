/**
 * @file NTabView.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-27
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_TABVIEW_H__
#define __NUI_TABVIEW_H__

#include "NTabBar.h"
#include "NScrollView.h"

namespace Nui 
{
    /**
     * @brief Articulates a TabBar in a ScrollView, and a ContentView inside another ScrollView. 
     * 
     * A TabView creates a TabBar in the desired position, and manages a content view inside the
     * TabView main area. The content view can be any view you want. For simplicity, a Document
     * class along with a DocumentView and a DocumentTabView are available for managing 
     * document like views. 
     * 
     * A TabBar calls its TabView's onSelectedIndex() method to notify the TabView an index
     * has been selected. The TabView then calls its internal method newContentView(index) 
     * to get the view for the selected index. 
     * 
     */
    class TabView : public View 
    {
        friend class TabBar; 
        
        //! @brief The TabBar View.
        Shared < TabBar > mTabBar;

        //! @brief The TabBar ScrollView.
        Shared < ScrollView > mTabBarScrollView;

        //! @brief The ContentView Scroller.
        Shared < ScrollView > mContentViewScroll;

    public: 

        //! @brief Creates a new TabView.
        TabView(Orientation orientation = Orientation::Horizontal, 
                Alignment align = Alignment::Left);

        //! @brief Layouts the two ScrollViews.
        void layoutChildren(void);

        //! @brief Returns the TabBar.
        inline Shared < TabBar > bar() const { return mTabBar; }

        //! @brief Returns the current content view.
        Shared < View > contentView() const;

        //! @brief Returns the currently selected index.
        ssize_t selectedIndex() const;

    protected:

        //! @brief Creates a new view for the given index.
        virtual Shared < View > newContentView(size_t index) const = 0;

    NUI_EVENT:

        //! @brief Creates the different TabView elements.
        virtual void attached(void);

        //! @brief Notifies the TabView an index has been selected.
        virtual void onSelectedIndex(size_t index);
    };
}

#endif 