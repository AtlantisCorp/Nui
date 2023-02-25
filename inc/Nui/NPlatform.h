/**
 * @file NPlatform.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-23
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_PLATFORM_H__
#define __NUI_PLATFORM_H__

#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <any>
#include <map>
#include <algorithm>
#include <optional>
#include <functional>
#include <filesystem>

#if defined(__APPLE__)
#
#   include <objc/objc-runtime.h>
#   define NUI_PLATFORM_APPLE 1
# 
#   if defined(__OBJC__) 
#       define NUI_LANGUAGE_OBJC 1
#       include <Cocoa/Cocoa.h> 
#       define NUI_OBJC_HDL(TYPE) TYPE*
#       define NUI_OBJC_INT(TYPE) id < TYPE >
#   else  
#       define NUI_OBJC_HDL(TYPE) id
#       define NUI_OBJC_INT(TYPE) id
#   endif 
# 
#   if defined(__IOS__) 
#   else  
#   endif 
# 
#endif 

#if NUI_LANGUAGE_OBJC 
#   define NUI_EVENT public
#else  
#   define NUI_EVENT protected
#endif

namespace std 
{
    typedef std::map < std::string, std::any > dictionnary;
}

namespace fs = std::filesystem;
using namespace std::string_literals;

namespace Nui
{
    template < typename T > using Shared = std::shared_ptr < T >;
    template < typename T > using Weak = std::weak_ptr < T >;
    
    template < typename T, typename... Args > Shared < T > Make(Args&&... args)
    {
        return std::make_shared < T >(std::forward < Args >(args)...);
    }
}

#endif
