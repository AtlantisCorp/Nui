/**
 * @file NScrollView.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_SCROLLVIEW_H__
#define __NUI_SCROLLVIEW_H__

#include "NView.h"

namespace Nui 
{
    /**
     * @brief A view that clips another view. 
     * 
     */
    class ScrollView : public View 
    {
        //! @brief The scrolled view.
        Shared < View > mContentView;

    public: 

        //! @brief Creates a new ScrollView.
        ScrollView(const Rect& frameRect = {});

        //! @brief Returns the scrolled view.
        inline const auto& contentView() const { return mContentView; }

        //! @brief Sets the content view.
        virtual void setContentView(const Shared < View >& view);
        
        //! @brief Sets the scroll view frame.
        virtual void setFrame(const Rect& frameRect);
    };
}

#endif 
