/**
 * @file NScrollView.mm
 * @author Luk2010
 * @brief
 * @version 0.1
 * @date 2023-02-24
 *
 * @copyright Atlanti's Corp @2023
 *
 */

#include "Nui/NScrollView.h"

@interface NScrollView : NSScrollView
@end

@implementation NScrollView

- (id)initWithFrame:(NSRect)frameRect
{
    self = [super initWithFrame:frameRect];
    if (self) {
        self.translatesAutoresizingMaskIntoConstraints = NO;
        self.contentView.frame = frameRect;
    }
    return self;
}

- (BOOL)isFlipped
{
    return YES;
}

@end

@interface NClipView : NSClipView
@end

@implementation NClipView

- (BOOL)isFlipped
{
    return YES;
}

@end

Nui::ScrollView::ScrollView(const Rect& frameRect):
Nui::View([[NScrollView alloc] initWithFrame:NSMakeRect(frameRect.origin.x,
                                                         frameRect.origin.y,
                                                         frameRect.size.width,
                                                         frameRect.size.height)])
{
    ((NScrollView*)handle()).canDrawSubviewsIntoLayer = YES;
    ((NScrollView*)handle()).drawsBackground = NO;
    ((NScrollView*)handle()).autohidesScrollers = YES;
    ((NScrollView*)handle()).hasHorizontalScroller = YES;
}

void Nui::ScrollView::setContentView(const Nui::Shared < Nui::View >& view)
{
    Nui::View::addChild(view);
    [view->handle() removeFromSuperview];
    
    if (mContentView) {
        Nui::View::removeChild(mContentView);
    }
    
    mContentView = view;
    ((NSScrollView*)handle()).documentView = view->handle();
}

void Nui::ScrollView::setFrame(const Rect& frameRect)
{
    Nui::View::setFrame(frameRect);
}
