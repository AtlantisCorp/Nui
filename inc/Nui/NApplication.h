/**
 * @file NApplication.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-23
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_APPLICATION_H__
#define __NUI_APPLICATION_H__

#include "NPlatform.h"
#include "NModuleManager.h"

namespace Nui 
{
    /**
     * @brief An Application class.
     * 
     * You must derive from this class to create a standard Nui Application. Implement the function
     * initialize() to create a new Window. 
     * 
     */
    class Application
    {
#       if NUI_PLATFORM_APPLE 

        //! @brief The OBJC NSApplication handle.
        NUI_OBJC_HDL(NSApplication) mHandle;

        //! @brief The NSApplication delegate.
        NUI_OBJC_INT(NSApplicationDelegate) mDelegateHandle;

#       endif 

#       if NUI_PLATFORM_WIN32 

        //! @brief Boolean true if the application should terminate on next loop.
        BOOL mShouldTerminate;

#       endif 

    protected:

#       if NUI_PLATFORM_APPLE

        //! @brief Constructs a new Application from a NSApplication handle.
        Application(NUI_OBJC_HDL(NSApplication) handle);

#       endif 

    public:
        
        //! @brief Returns the current Application.
        static Application& Get();

        //! @brief Constructs a new Application.
        Application(void);

        //! @brief Runs the application event loop.
        virtual void run(void);

        //! @brief Terminates the application.
        virtual void terminate(void);

        //! @brief Returns if the application should close after its last window did.
        virtual inline bool shouldCloseAfterLastWindowClosed(void) const { return true; }

        //! @brief The module manager.
        ModuleManager moduleManager;
        
        //! @brief Returns the path for the resource directory.
        virtual fs::path resourcePath() const;

    NUI_EVENT: 

        //! @brief Initializes the application after its launching.
        virtual void initialize(void) { }

        //! @brief The application will terminate.
        virtual void willTerminate(void) { }
    };
}

#endif 
