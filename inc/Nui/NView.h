/**
 * @file NView.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-23
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_VIEW_H__
#define __NUI_VIEW_H__

#include "NPlatform.h"
#include "NRect.h"
#include "NColor.h"
#include "NMouseButton.h"
#include "NViewState.h"
#include "NViewStyle.h"

namespace Nui 
{
    /**
     * @brief The basic block of Nui UI. 
     * 
     * The view layout is determined by the layout() method. This method is called whenever the view
     * content is changed (updateLayout() is called). This means that when modifying your view, you 
     * should always call updateLayout(). The view's layout is modified only when this function is 
     * called, which means you can do multiple changes and then call updateLayout(). 
     * 
     * @note You must always call View::layout() in your layout override, at the end of your function
     *       or before updating children layout. 
     * 
     */
    class View : public std::enable_shared_from_this < View >
    {
        friend class Window;
        
#       if NUI_PLATFORM_APPLE 

        //! @brief The NSView handle.
        NUI_OBJC_HDL(NSView) mHandle;
        
        //! @brief The NSResponder handle.
        NUI_OBJC_HDL(NSResponder) mHandleResponder;
        
        //! @brief The NSTrackingArea area to track mouse moved events.
        NUI_OBJC_HDL(NSTrackingArea) mTrackingArea;

#       endif 

        //! @brief The view's frame.
        Rect mFrame;
        
        //! @brief The Window for this view.
        class Window* mWindow;
        
        //! @brief The parent view.
        Weak < View > mParentView;

        //! @brief The background color.
        Color mBackgroundColor;
        
        //! @brief The children's list.
        std::vector < Shared < View > > mChildren;
        
        //! @brief The view's name.
        std::string mName;
        
        //! @brief The border color.
        Color mBorderColor;
        
        //! @brief The border width.
        double mBorderWidth;
        
        //! @brief A custom intrinsicContentSize. If this size is set, the method
        //! intrinsicContentSize() returns it. If not set, then the parent size is returned.
        //! Overridding the method intrinsicContentSize() should hide this behaviour.
        std::optional < Size > mIntrinsicContentSize;

        //! @brief The corner radius.
        double mCornerRadius;
        
    protected:

        //! @brief The view's styles by state.
        std::map < ViewState, ViewStyle > mStyles;

        //! @brief The current view's state.
        ViewState mState;

        //! @brief The view's default state. This is the state returned by defaultState(). You 
        //! can set this state to the desired value for when the view isn't hovered nor clicked.
        ViewState mDefaultState;

    protected:

#       if NUI_PLATFORM_APPLE

        //! @brief Creates a View from a NSView handle.
        View(NUI_OBJC_HDL(NSView) handle);
        
    public:
        
        //! @brief Returns the view's handle.
        inline NUI_OBJC_HDL(NSView) handle() const { return mHandle; }

#       endif 

    public:

        //! @brief Constructs a new view.
        //! @param frameRect The view frame.
        View(const Rect& frameRect = Rect());
        
        //! @brief Destructor.
        virtual ~View();

        //! @brief Returns the view's size, depending only on its content and parent.
        virtual inline Size intrinsicContentSize() const  
        {
            if (mIntrinsicContentSize.has_value()) {
                return mIntrinsicContentSize.value();
            }
            
            auto p = parentView();

            if (p) {
                return p->frame().size;
            }

            return mFrame.size;
        }

        //! @brief Layouts the view's children. 
        virtual void layoutChildren(void) { }

        //! @brief Updates the view's layout.
        virtual inline void updateLayout(void)
        {
            // First update the view's size.
            Size frameSize = intrinsicContentSize();
            setFrameSize(frameSize);
            
            // Updates the children size.
            updateChildrenLayout();
            
            // Sets the children's frame origins.
            layoutChildren();
        }
        
        //! @brief Updates the children layout.
        virtual inline void updateChildrenLayout(void)
        {
            for (auto& child : mChildren) {
                child->updateLayout();
            }
        }

        //! @brief Sets the view's frame.
        virtual void setFrame(const Rect& frameRect);

        //! @brief Sets the view's frame size.
        virtual void setFrameSize(const Size& frameSize);

        //! @brief Sets the view's frame origin.
        virtual void setFrameOrigin(const Point& origin);

        //! @brief Returns the view's frame.
        virtual inline Rect frame() const { return mFrame; }
        
        //! @brief Returns the view's window.
        virtual class Window* window() const; 

        //! @brief Sets the background color.
        virtual void setBackgroundColor(const Color& color);

        //! @brief Returns the background color.
        virtual inline Color backgroundColor() const { return mBackgroundColor; }
        
        //! @brief Inserts a child before given one.
        virtual void addChild(const Shared < View >& child, const Shared < View >& beforeChild = nullptr);
        
        //! @brief Returns the parent view.
        virtual inline Shared < View > parentView() const { return mParentView.lock(); }
        
        //! @brief Sets a name for the view.
        virtual inline void setName(const std::string& name) { mName = name; }
        
        //! @brief Returns the view's name.
        virtual inline const std::string& name() const { return mName; }
        
        //! @brief Returns the view's children with given name.
        virtual inline std::vector < Shared < View > > findChildrenByName(const std::string& name) const
        {
            std::vector < Shared < View > > res;
            for (auto const& child : mChildren) {
                if (child->name() == name) {
                    res.push_back(child);
                }
            }
            return res;
        }

        //! @brief Adds multiple children.
        template < typename... Args > 
        void addChildren(Args&&... children) 
        {
            ((addChild(children)), ...);
        }
        
        //! @brief Returns the border color.
        virtual inline const Color& borderColor() const { return mBorderColor; }
        
        //! @brief Sets the border color.
        virtual void setBorderColor(const Color& color);
        
        //! @brief Returns the border width.
        virtual inline double borderWidth() const { return mBorderWidth; }
        
        //! @brief Sets the border width.
        virtual void setBorderWidth(double value);
        
        //! @brief Sets the custom instrinsic content size.
        virtual inline void setIntrinsicContentSize(const Size& value) { mIntrinsicContentSize = value; }
        
        //! @brief Returns the previous view.
        virtual inline Shared < View > previousView() const
        {
            auto p = parentView();
            if (p) {
                auto indexOfSelf = p->indexOfChild(shared_from_this());
                if (indexOfSelf == 0 || indexOfSelf >= p->numberOfChildren()) {
                    return nullptr;
                }
                return p->childAt(indexOfSelf - 1);
            }
            return nullptr;
        }
        
        //! @brief Returns the next view.
        virtual inline Shared < View > nextView() const
        {
            auto p = parentView();
            if (p) {
                auto indexOfSelf = p->indexOfChild(shared_from_this());
                if (indexOfSelf >= p->numberOfChildren() - 1) {
                    return nullptr;
                }
                return p->childAt(indexOfSelf + 1);
            }
            return nullptr;
        }
        
        //! @brief Returns the index of a given view.
        virtual inline std::size_t indexOfChild(const Shared < const View >& child) const
        {
            auto it = std::find(mChildren.begin(), mChildren.end(), child);
            return std::distance(mChildren.begin(), it);
        }
        
        //! @brief Returns the number of children.
        virtual inline std::size_t numberOfChildren(void) const
        {
            return mChildren.size();
        }
        
        //! @brief Returns the child at given index.
        virtual inline Shared < View > childAt(std::size_t index) const
        {
            return mChildren[index];
        }

        //! @brief Returns the corner radius.
        virtual inline double cornerRadius() const { return mCornerRadius; }

        //! @brief Sets the corner radius.
        virtual void setCornerRadius(double radius);

        //! @brief Returns all the children of this view.
        inline const auto& children() const { return mChildren; }
        
        //! @brief Removes a child from this view.
        virtual void removeChild(const Shared < View >& view);

        //! @brief Updates the view's style.
        virtual void updateStyle(const ViewStyle& style);

        //! @brief Sets the style for the given state.
        virtual inline void setStyle(ViewState state, const ViewStyle& style)
        {
            mStyles[state] = style;

            if (mState == state) {
                updateStyle(style);
            }
        }

        //! @brief Returns the style for given state.
        virtual inline const ViewStyle& style(ViewState state = ViewState::Neutral) const 
        {
            if (mStyles.contains(state)) {
                return mStyles.at(state);
            }
            return mStyles.at(ViewState::Neutral);
        }
        
        //! @brief Returns true if a point is in the view's rect.
        virtual bool windowPointIsInFrame(const Point& location) const;

        //! @brief Returns the default state.
        virtual ViewState defaultState() const { return mDefaultState; }

        //! @brief Sets the default state.
        virtual void setDefaultState(ViewState state) 
        {
            if (mState == mDefaultState && state != mDefaultState) {
                mState = state;
                updateStyle(style(state));
            }
            mDefaultState = state;
        }

    NUI_EVENT:
        
        //! @brief The view is attached to a parent view.
        virtual void attached(void) {}
        
        //! @brief The view is detached from a parent view.
        virtual void detached(void) {}

        //! @brief The mouse has been pressed in the view.
        virtual void onMouseDown(MouseButton button, const Point& location)
        {
            auto p = parentView();
            
            if (p) {
                p->onMouseDown(button, location);
            }
            
            if (mState == ViewState::Hovered) {
                mState = ViewState::Clicked;
                updateStyle(style(mState));
            }
        }
        
        //! @brief The mouse has been released in the view.
        virtual void onMouseUp(MouseButton button, const Point& location)
        {
            auto p = parentView();
            
            if (p) {
                p->onMouseUp(button, location);
            }
            
            if (mState == ViewState::Clicked) {
                if (windowPointIsInFrame(location)) {
                    mState = ViewState::Hovered;
                }
                else {
                    mState = ViewState::Neutral;
                }
                updateStyle(style(mState));
            }
        }
        
        //! @brief The mouse has moved in the view.
        virtual void onMouseMoved(double deltaX, double deltaY) { }
        
        //! @brief The mouse has entered the view.
        virtual inline void onMouseEnter(const Point& location)
        {
            if (mState != ViewState::Clicked) {
                mState = ViewState::Hovered;
                updateStyle(style(mState));
            }
        }
        
        //! @brief The mouse has exited the view.
        virtual inline void onMouseExit(const Point& location)
        {
            if (mState == ViewState::Hovered) {
                mState = defaultState();
                updateStyle(style(mState));
            }
        }
    };
}

#endif // !__NUI_VIEW_H__
