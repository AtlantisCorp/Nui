/**
 * @file NSView+NView.mm
 * @author Luk2010
 * @brief
 * @version 0.1
 * @date 2023-02-26
 *
 * @copyright Atlanti's Corp @2023
 *
 */

#include "Nui/macos/NSView+NView.h"

static const char kNSViewNuiViewKey = 0;

@implementation NSView (NView)

- (Nui::View*) NuiNView
{
    NSData* data = (NSData*) objc_getAssociatedObject(self, &kNSViewNuiViewKey);
    
    if (!data) {
        return NULL;
    }
    
    return (Nui::View*) data.bytes;
}

- (void) setNuiNView:(Nui::View *)view
{
    NSData* data = [NSData dataWithBytesNoCopy:view
                                        length:sizeof(Nui::View)
                                  freeWhenDone:NO];
    
    objc_setAssociatedObject(self,
                             &kNSViewNuiViewKey,
                             data,
                             OBJC_ASSOCIATION_RETAIN);
}

@end
