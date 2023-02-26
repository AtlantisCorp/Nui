/**
 * @file NTextControl.mm
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "Nui/NTextControl.h"

@interface NPfnHandler : NSObject
{
    Nui::TextControl* _control;
}

- (id)initWithNui:(Nui::TextControl*)control;
- (void)action;

@end

@implementation NPfnHandler

- (id)initWithNui:(Nui::TextControl *)control
{
    self = [super init];
    if (self) {
        _control = control;
    }
    return self;
}

- (void)action
{
    if (_control) {
        _control->action();
    }
}

@end

Nui::TextControl::TextControl(NUI_OBJC_HDL(NSControl)handle):
Nui::View(handle)
{
    mPfnHandler = [[NPfnHandler alloc] initWithNui:this];
    handle.target = mPfnHandler;
    handle.action = @selector(action);
}

void Nui::TextControl::setText(const std::string &text)
{
    ((NSControl*)handle()).stringValue = @(text.data());
    mText = text;
}

void Nui::TextControl::setFont(const Shared<Font> &font)
{
    ((NSControl*)handle()).font = font->handle();
    mFont = font;
    mStyles[ViewState::Neutral].font = font;
}

void Nui::TextControl::setTextColor(const Color &color)
{
    if ([handle() respondsToSelector:@selector(setTextColor:)]) {
        [handle() performSelector:@selector(setTextColor:)
                       withObject:[NSColor colorWithRed:color.red
                                                  green:color.green
                                                   blue:color.blue
                                                  alpha:color.alpha]];
    }
    mTextColor = color;
    mStyles[ViewState::Neutral].textColor = color;
}

Nui::Size Nui::TextControl::preferredSize() const
{
    return Size
    {
        ((NSControl*)handle()).intrinsicContentSize.width,
        ((NSControl*)handle()).intrinsicContentSize.height
    };
}

void Nui::TextControl::setTextAlign(TextAlign value)
{
    mTextAlign = value;
    mStyles[ViewState::Neutral].textAlign = value;
    switch (value) {
        case TextAlign::Left:
            ((NSControl*)handle()).alignment = NSTextAlignmentLeft;
            break;
        case TextAlign::Center:
            ((NSControl*)handle()).alignment = NSTextAlignmentCenter;
            break;
        case TextAlign::Right:
            ((NSControl*)handle()).alignment = NSTextAlignmentRight;
            break;
        case TextAlign::Justified:
            ((NSControl*)handle()).alignment = NSTextAlignmentJustified;
            break;
        case TextAlign::Natural:
            ((NSControl*)handle()).alignment = NSTextAlignmentNatural;
            break;
    }
}

void Nui::TextControl::updateStyle(const ViewStyle& style)
{
    View::updateStyle(style);
    if (style.textAlign.has_value()) {
        switch (style.textAlign.value()) {
            case TextAlign::Left:
                ((NSControl*)handle()).alignment = NSTextAlignmentLeft;
                break;
            case TextAlign::Center:
                ((NSControl*)handle()).alignment = NSTextAlignmentCenter;
                break;
            case TextAlign::Right:
                ((NSControl*)handle()).alignment = NSTextAlignmentRight;
                break;
            case TextAlign::Justified:
                ((NSControl*)handle()).alignment = NSTextAlignmentJustified;
                break;
            case TextAlign::Natural:
                ((NSControl*)handle()).alignment = NSTextAlignmentNatural;
                break;
        }
    }
    if (style.textColor.has_value()) {
        if ([handle() respondsToSelector:@selector(setTextColor:)]) {
            [handle() performSelector:@selector(setTextColor:)
                           withObject:[NSColor colorWithRed:style.textColor.value().red
                                                      green:style.textColor.value().green
                                                       blue:style.textColor.value().blue
                                                      alpha:style.textColor.value().alpha]];
        }
    }
}
