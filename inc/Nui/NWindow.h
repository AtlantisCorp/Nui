/**
 * @file NWindow.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-23
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_WINDOW_H__
#define __NUI_WINDOW_H__

#include "NPlatform.h"
#include "NRect.h"
#include "NWindowStyle.h"
#include "NView.h"

namespace Nui
{
    /**
     * @brief A Window instance class.
     * 
     * This represents a surface on the screen where views are displayed. On desktop applications,
     * a window is a regular rectangle. On mobile applications, this represents the main screen and
     * only one window is available. 
     * 
     */
    class Window 
    {
#       if NUI_PLATFORM_APPLE
        
        //! @brief The NSWindow instance.
        NUI_OBJC_HDL(NSWindow) mHandle;
        
        //! @brief The NSWindowDelegate instance.
        NUI_OBJC_INT(NSWindowDelegate) mDelegateHandle;

#       endif
        
        //! @brief The content view.
        Shared < View > mContentView;
        
    protected:
        
#       if NUI_PLATFORM_APPLE
        
        //! @brief Creates a new Window from an OBJ C handle.
        Window(NUI_OBJC_HDL(NSWindow) handle);
        
#       endif
        
    public:
        
        //! @brief Creates a new Window.
        //! @param frameRect The frame for the new window.
        //! @param title The Window's title.
        //! @param style The window's style.
        Window(const Rect& frameRect, std::string_view title, const WindowStyle& style = {});
        
        //! @brief Shows the window on screen.
        virtual void show(void);
        
        //! @brief Closes the window.
        virtual void close(void);
        
        //! @brief Sets the content view.
        virtual void setContentView(const Shared < View >& view);
        
        //! @brief Returns the content view.
        virtual inline Shared < View > contentView() const { return mContentView; }
        
        //! @brief Returns the content frame rectangle.
        virtual Rect contentFrame() const;
    };
}

#endif 
