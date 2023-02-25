/**
 * @file NSButtonWithImagePadding.mm
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-25
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "Nui/macos/NSButtonWithImageSpacing.h"

@implementation NSButtonWithImageSpacing

@synthesize verticalPadding;
@synthesize horizontalPadding;

- (void)drawRect:(NSRect)dirtyRect
{
    NSRect originalBounds = self.bounds;
    
    self.bounds = NSInsetRect(originalBounds,
                              self.horizontalPadding,
                              self.verticalPadding);
    
    [super drawRect:dirtyRect];
    self.bounds = originalBounds;
}

@end
