/**
 * @file NSView+NView.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_NSVIEWPLUSNVIEW_H__
#define __NUI_NSVIEWPLUSNVIEW_H__

#include "../NPlatform.h"
#include "../NView.h"

@interface NSView (NView)

- (Nui::View*) NuiNView ;

- (void) setNuiNView:(Nui::View*) view ;

@end

#endif
