/**
 * @file NApplication.mm
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-23
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "Nui/NApplication.h"

@interface NApplicationDelegate : NSObject < NSApplicationDelegate > 
{
    Nui::Application* _app;
}

- (id)initWithNui:(Nui::Application*)app;

@end 

@implementation NApplicationDelegate

- (id)initWithNui:(Nui::Application*)app 
{
    self = [super init];
    if (self) {
        _app = app;
    }
    return self;
}

- (void)applicationDidFinishLaunching:(NSNotification*)notification 
{
    if (_app) {
        _app->initialize();
    }
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSNotification*)notification
{
    if (_app) {
        return _app->shouldCloseAfterLastWindowClosed();
    }
    return NO;
}

- (void)applicationWillTerminate:(NSNotification*)notification
{
    if (_app) {
        _app->willTerminate();
    }
}

@end 

namespace Nui 
{
    Application* mGlobalApp = NULL;
    
    Application& Application::Get()
    {
        return *mGlobalApp;
    }
    
    Application::Application(NUI_OBJC_HDL(NSApplication) handle) 
    {
        if (mGlobalApp != NULL) {
            throw std::runtime_error("Nui:Application: Another application instance is already running.");
        }
        if (!handle) {
            throw std::invalid_argument("Nui:Application: 'handle' parameter is nil.");
        }
        mGlobalApp = this;
        mHandle = handle;
        mDelegateHandle = [[NApplicationDelegate alloc] initWithNui:this];
        mHandle.delegate = mDelegateHandle;
    }

    Application::Application()
    {
        if (mGlobalApp != NULL) {
            throw std::runtime_error("Nui:Application: Another application instance is already running.");
        }
        mGlobalApp = this;
        mHandle = NSApp = [NSApplication sharedApplication];
        mDelegateHandle = [[NApplicationDelegate alloc] initWithNui:this];
        mHandle.delegate = mDelegateHandle;
        mHandle.activationPolicy = NSApplicationActivationPolicyRegular;
    }

    void Application::run() 
    {
        [mHandle run];
    }

    void Application::terminate() 
    {
        [mHandle terminate:nil];
    }
}
