/**
 * @file NButton.mm
 * @author Luk2010
 * @brief
 * @version 0.1
 * @date 2023-02-24
 *
 * @copyright Atlanti's Corp @2023
 *
 */

#include "Nui/NButton.h"

Nui::Button::Button(std::string_view title, const std::function < void(TextControl const&) >& handler):
Nui::TextControl([NSButton buttonWithTitle:@(title.data())
                                    target:nil
                                    action:nil])
{
    setActionHandler(handler);
    
    NSButton* hdl = (NSButton*)handle();
    [hdl setButtonType:NSButtonTypeMomentaryPushIn];
    [hdl setBezelStyle:NSBezelStyleRoundRect];
    
    mButtonType = ButtonType::MomentaryPushIn;
}

void Nui::Button::setButtonType(ButtonType type)
{
    if (type == mButtonType) {
        return;
    }
    mButtonType = type;
    NSButtonCell* cell = (NSButtonCell*) ((NSButton*)handle()).cell;
    
    switch (type) {
        case ButtonType::Custom:
            [((NSButton*)handle()) setButtonType:NSButtonTypeMomentaryPushIn];
            cell.bezeled = NO;
            cell.bordered = NO;
            cell.highlightsBy = NSContentsCellMask;
            break;
        case ButtonType::MomentaryPushIn:
            [((NSButton*)handle()) setButtonType:NSButtonTypeMomentaryPushIn];
            ((NSButton*)handle()).cell.bezeled = YES;
            ((NSButton*)handle()).cell.bordered = YES;
            break;
        case ButtonType::PushOnPushOff:
            [((NSButton*)handle()) setButtonType:NSButtonTypePushOnPushOff];
            break;
        case ButtonType::Radio:
            [((NSButton*)handle()) setButtonType:NSButtonTypeRadio];
            break;
        case ButtonType::CheckBox:
            [((NSButton*)handle()) setButtonType:NSButtonTypeSwitch];
            break;
        case ButtonType::Accelerator:
            [((NSButton*)handle()) setButtonType:NSButtonTypeAccelerator];
            break;
        case ButtonType::MultiLevelAccelerator:
            [((NSButton*)handle()) setButtonType:NSButtonTypeMultiLevelAccelerator];
            break;
    }
}

void Nui::Button::setTextColor(const Color &color)
{
    Nui::TextControl::setTextColor(color);
    
    NSMutableAttributedString* title = [[NSMutableAttributedString alloc] initWithAttributedString:((NSButton*)handle()).attributedTitle];
    
    [title addAttribute:NSForegroundColorAttributeName
                  value:[NSColor colorWithRed:color.red
                                        green:color.green
                                         blue:color.blue
                                        alpha:color.alpha]
                  range:NSMakeRange(0, title.length)];
    
    ((NSButton*)handle()).attributedTitle = title;
}

void Nui::Button::setAlternateTextColor(const Color &color)
{
    mAlternateTextColor = color;
    
    NSMutableAttributedString* title = [[NSMutableAttributedString alloc] initWithAttributedString:((NSButton*)handle()).attributedAlternateTitle];
    
    [title removeAttribute:NSForegroundColorAttributeName
                     range:NSMakeRange(0, title.length)];
    
    [title addAttribute:NSForegroundColorAttributeName
                  value:[NSColor colorWithRed:color.red
                                        green:color.green
                                         blue:color.blue
                                        alpha:color.alpha]
                  range:NSMakeRange(0, title.length)];
    
    ((NSButton*)handle()).attributedAlternateTitle = title;
}

void Nui::Button::setAlternateText(std::string_view text)
{
    mAlternateText = (std::string) text;
    ((NSButton*)handle()).alternateTitle = @(text.data());
}
