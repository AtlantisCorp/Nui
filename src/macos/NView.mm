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

@interface NResponder : NSResponder
{
    Nui::View* _view;
}

- (id)initWithView:(Nui::View*)view;

@end

@implementation NResponder

- (id)initWithView:(Nui::View *)view
{
    self = [super init];
    if (self) {
        _view = view;
    }
    return self;
}

- (void)mouseDown:(NSEvent *)event
{
    if (_view) {
        _view->onMouseDown(Nui::MouseButton::Left, Nui::Point{
            NSEvent.mouseLocation.x,
            NSEvent.mouseLocation.y
        });
    }
    [super mouseDown:event];
}

- (void)mouseUp:(NSEvent *)event
{
    if (_view) {
        _view->onMouseUp(Nui::MouseButton::Left, Nui::Point{
            NSEvent.mouseLocation.x,
            NSEvent.mouseLocation.y
        });
    }
    [super mouseDown:event];
}

- (void)mouseMoved:(NSEvent *)event
{
    if (_view) {
        _view->onMouseMoved(event.deltaX, event.deltaY);
    }
    [super mouseMoved:event];
}

- (void)mouseEntered:(NSEvent *)event
{
    if (_view) {
        _view->onMouseEnter(Nui::Point{
            NSEvent.mouseLocation.x,
            NSEvent.mouseLocation.y
        });
    }
    [super mouseEntered:event];
}

- (void)mouseExited:(NSEvent *)event
{
    if (_view) {
        _view->onMouseExit(Nui::Point{
            NSEvent.mouseLocation.x,
            NSEvent.mouseLocation.y
        });
    }
    [super mouseExited:event];
}

@end

Nui::View::View(NUI_OBJC_HDL(NSView) handle)
{
    mHandle = handle;
    mBorderWidth = 0;
    mHandle.wantsLayer = YES;
    mHandleResponder = [[NResponder alloc] initWithView:this];
    mHandle.nextResponder = mHandleResponder;
    setBackgroundColor({ .0, .0, .0, .0 });
    
    mTrackingArea = [[NSTrackingArea alloc] initWithRect:mHandle.frame
                                                 options:NSTrackingMouseMoved |
                                                         NSTrackingMouseEnteredAndExited |
                                                         NSTrackingActiveInKeyWindow
                                                   owner:mHandle
                                                userInfo:nil];
    [mHandle addTrackingArea:mTrackingArea];
    
    mStyles[ViewState::Neutral] = ViewStyle { };
    mState = ViewState::Neutral;
}

Nui::View::View(const Rect& frameRect)
{
    mHandle = [[NView alloc] initWithFrame:NSMakeRect(frameRect.origin.x,
                                                      frameRect.origin.y,
                                                      frameRect.size.width,
                                                      frameRect.size.height)
                                      view:this];
    mHandle.wantsLayer = YES;
    mHandleResponder = [[NResponder alloc] initWithView:this];
    mHandle.nextResponder = mHandleResponder;
    mBorderWidth = 0;
    setBackgroundColor({ .0, .0, .0, .0 });
    
    mTrackingArea = [[NSTrackingArea alloc] initWithRect:mHandle.frame
                                                 options:NSTrackingMouseMoved |
                                                         NSTrackingMouseEnteredAndExited |
                                                         NSTrackingActiveInKeyWindow
                                                   owner:mHandle
                                                userInfo:nil];
    [mHandle addTrackingArea:mTrackingArea];
    
    mStyles[ViewState::Neutral] = ViewStyle { };
    mState = ViewState::Neutral;
}

Nui::View::~View()
{
    [mHandle removeTrackingArea:mTrackingArea];
}

void Nui::View::setFrame(const Rect &frameRect)
{
    mFrame = frameRect;
    
    mHandle.frame = NSMakeRect(mFrame.origin.x,
                               mFrame.origin.y,
                               mFrame.size.width,
                               mFrame.size.height);
    
    [mHandle removeTrackingArea:mTrackingArea];
    
    mTrackingArea = [[NSTrackingArea alloc] initWithRect:mHandle.frame
                                                 options:NSTrackingMouseMoved |
                                                         NSTrackingMouseEnteredAndExited |
                                                         NSTrackingActiveInKeyWindow
                                                   owner:mHandle
                                                userInfo:nil];
    [mHandle addTrackingArea:mTrackingArea];
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
    mStyles[ViewState::Neutral].backgroundColor = color;
}

void Nui::View::addChild(const Shared < View >& child, const Shared < View >& beforeChild)
{
    [mHandle addSubview:child->handle()
             positioned:NSWindowBelow
             relativeTo:beforeChild ? beforeChild->handle() : nil];
    
    mChildren.insert(std::find(mChildren.begin(), mChildren.end(), beforeChild), child);
    child->mParentView = shared_from_this();
    child->attached();
    
    if (child->mHandle.nextResponder != child->mHandleResponder) {
        child->mHandleResponder.nextResponder = child->mHandle.nextResponder;
        child->mHandle.nextResponder = child->mHandleResponder;
    }
}

void Nui::View::setBorderColor(const Nui::Color& color)
{
    mBorderColor = color;
    mHandle.layer.borderColor = [NSColor colorWithRed:color.red
                                                green:color.green
                                                 blue:color.blue
                                                alpha:color.alpha].CGColor;
    mStyles[ViewState::Neutral].borderColor = color;
}

void Nui::View::setBorderWidth(double value)
{
    mBorderWidth = value;
    mHandle.layer.borderWidth = value;
    mStyles[ViewState::Neutral].borderWidth = value;
}

void Nui::View::setCornerRadius(double radius)
{
    mCornerRadius = radius;
    mHandle.layer.cornerRadius = radius;
    mStyles[ViewState::Neutral].cornerRadius = radius;
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

void Nui::View::updateStyle(const ViewStyle& style)
{
    if (style.backgroundColor.has_value()) {
        mHandle.layer.backgroundColor = [NSColor colorWithRed:style.backgroundColor.value().red
                                                        green:style.backgroundColor.value().green
                                                         blue:style.backgroundColor.value().blue
                                                        alpha:style.backgroundColor.value().alpha].CGColor;
    }
    if (style.borderColor.has_value()) {
        mHandle.layer.borderColor = [NSColor colorWithRed:style.borderColor.value().red
                                                    green:style.borderColor.value().green
                                                     blue:style.borderColor.value().blue
                                                    alpha:style.borderColor.value().alpha].CGColor;
    }
    if (style.borderWidth.has_value()) {
        mHandle.layer.borderWidth = style.borderWidth.value();
    }
    if (style.cornerRadius.has_value()) {
        mHandle.layer.cornerRadius = style.cornerRadius.value();
    }
}

bool Nui::View::windowPointIsInFrame(const Point &location) const
{
    CGPoint localCoords = [mHandle convertPoint:NSMakePoint(location.x, location.y)
                                       fromView:nil];
    return CGRectContainsPoint(mHandle.frame, localCoords);
}
