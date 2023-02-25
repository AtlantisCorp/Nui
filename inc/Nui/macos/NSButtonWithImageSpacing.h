/**
 * @file NSButtonWithImageSpacing.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-25
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_NSBUTTONWITHIMAGESPACING_H__
#define __NUI_NSBUTTONWITHIMAGESPACING_H__

#include "../NPlatform.h"

/**
 * @brief A NSButton derived class that uses a vertical and a horizontal spacing 
 *        property.
 * 
 */
@interface NSButtonWithImageSpacing : NSButton 
@property CGFloat verticalPadding;
@property CGFloat horizontalPadding;
@end

#endif 