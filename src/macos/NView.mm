/**
 * @file NView.mm
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-23
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "Nui/NView.h"

@interface NView : NSView
{
    Nui::View* _view;
}

- (id)initWithFrame:(NSRect)frameRect view:(Nui::View*)view;

@end

@implementation NView

- (id)initWithFrame:(NSRect)frameRect view:(Nui::View *)view
{
    self = [super initWithFrame:frameRect];
    if (self) {
        _view = view;
        self.translatesAutoresizingMaskIntoConstraints = NO;
    }
    return self;
}

- (BOOL)isFlipped
{
    return YES;
}

@end

Nui::View::View(NUI_OBJC_HDL(NSView) handle)
{
    mHandle = handle;
    mBorderWidth = 0;
    mHandle.wantsLayer = YES;
    setBackgroundColor({ .0, .0, .0, .0 });
}

Nui::View::View(const Rect& frameRect)
{
    mHandle = [[NView alloc] initWithFrame:NSMakeRect(frameRect.origin.x,
                                                      frameRect.origin.y,
                                                      frameRect.size.width,
                                                      frameRect.size.height)
                                      view:this];
    mHandle.wantsLayer = YES;
    mBorderWidth = 0;
    setBackgroundColor({ .0, .0, .0, .0 });
}

Nui::View::~View()
{
    
}

void Nui::View::setFrame(const Rect &frameRect)
{
    mFrame = frameRect;
    mHandle.frame = NSMakeRect(mFrame.origin.x,
                               mFrame.origin.y,
                               mFrame.size.width,
                               mFrame.size.height);
}

void Nui::View::setFrameSize(const Size &frameSize)
{
    setFrame({ mFrame.origin, frameSize });
}

void Nui::View::setFrameOrigin(const Point &origin)
{
    setFrame({ origin, mFrame.size });
}

class Nui::Window* Nui::View::window() const
{
    if (mWindow) {
        return mWindow;
    }
    if (!mParentView.expired()) {
        return mParentView.lock()->window();
    }
    return NULL;
}

void Nui::View::setBackgroundColor(const Color& color)
{
    mBackgroundColor = color;
    mHandle.layer.backgroundColor = [NSColor colorWithRed:color.red
                                                    green:color.green
                                                     blue:color.blue
                                                    alpha:color.alpha].CGColor;
}

void Nui::View::addChild(const Shared < View >& child, const Shared < View >& beforeChild)
{
    [mHandle addSubview:child->handle()
             positioned:NSWindowBelow
             relativeTo:beforeChild ? beforeChild->handle() : nil];
    
    mChildren.insert(std::find(mChildren.begin(), mChildren.end(), beforeChild), child);
    child->mParentView = shared_from_this();
    child->attached();
}

void Nui::View::setBorderColor(const Nui::Color& color)
{
    mBorderColor = color;
    mHandle.layer.borderColor = [NSColor colorWithRed:color.red
                                                green:color.green
                                                 blue:color.blue
                                                alpha:color.alpha].CGColor;
}

void Nui::View::setBorderWidth(double value)
{
    mBorderWidth = value;
    mHandle.layer.borderWidth = value;
}

void Nui::View::setCornerRadius(double radius)
{
    mCornerRadius = radius;
    mHandle.layer.cornerRadius = radius;
}

void Nui::View::removeChild(const Shared < View >& view)
{
    if (std::erase(mChildren, view) > 0) {
        [view->handle() removeFromSuperview];
        view->mParentView.reset();
        view->mWindow = NULL;
        view->detached();
    }
}
