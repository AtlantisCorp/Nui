/**
 * @file NWindow.mm
 * @author Luk2010
 * @brief
 * @version 0.1
 * @date 2023-02-23
 *
 * @copyright Atlanti's Corp @2023
 *
 */

#include "Nui/NWindow.h"

@interface NWindowDelegate : NSObject < NSWindowDelegate >
{
    Nui::Window* _window;
}

- (id)initWithNui:(Nui::Window*)window;

@end

@implementation NWindowDelegate

- (id)initWithNui:(Nui::Window*)window
{
    self = [super init];
    if (self) {
        _window = window;
    }
    return self;
}

- (void)windowDidResize:(NSNotification *)notification
{
    if (_window) {
        auto contentView = _window->contentView();
        if (contentView) {
            contentView->setFrame(_window->contentFrame());
            contentView->updateLayout();
        }
    }
}

@end

Nui::Window::Window(NUI_OBJC_HDL(NSWindow) handle)
{
    if (!handle) {
        throw std::invalid_argument("Nui:Window: 'handle' is nil.");
    }
    mHandle = handle;
    mHandle.delegate = mDelegateHandle = [[NWindowDelegate alloc] initWithNui:this];
    mHandle.releasedWhenClosed = NO;
}

Nui::Window::Window(const Rect& frameRect, std::string_view title, const WindowStyle& style)
{
    NSWindowStyleMask styleMask = 0;
    if (style.closable) styleMask |= NSWindowStyleMaskClosable;
    if (style.resizable) styleMask |= NSWindowStyleMaskResizable;
    if (style.titled) styleMask |= NSWindowStyleMaskTitled;
    mHandle = [[NSWindow alloc] initWithContentRect:NSMakeRect(frameRect.origin.x,
                                                               frameRect.origin.y,
                                                               frameRect.size.width,
                                                               frameRect.size.height)
                                          styleMask:styleMask
                                            backing:NSBackingStoreBuffered
                                              defer:NO];
    mHandle.delegate = mDelegateHandle = [[NWindowDelegate alloc] initWithNui:this];
    mHandle.releasedWhenClosed = NO;
    if (!title.empty()) {
        mHandle.title = @(title.data());
    }
}

void Nui::Window::show()
{
    [mHandle makeKeyAndOrderFront:nil];
}

void Nui::Window::close()
{
    [mHandle performClose:nil];
}

void Nui::Window::setContentView(const Shared < View >& view)
{
    if (mContentView) {
        mContentView->mWindow = NULL;
    }
    
    mContentView = view;
    
    if (mContentView) {
        mContentView->mWindow = this;
        mContentView->attached();
        
        mContentView->setFrame(contentFrame());
        mContentView->updateLayout();
        
        mHandle.contentView = mContentView->handle();
    }
}

Nui::Rect Nui::Window::contentFrame() const
{
    return {
        { mHandle.contentLayoutRect.origin.x, mHandle.contentLayoutRect.origin.y },
        { mHandle.contentLayoutRect.size.width, mHandle.contentLayoutRect.size.height }
    };
}
