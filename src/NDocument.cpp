/**
 * @file NDocument.cpp
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "Nui/NDocument.h"

namespace Nui 
{
    Document::Document()
    {

    }

    void Document::setTitle(const std::string& title)
    {
        mTitle = title;
    }

    const std::string& Document::title() const 
    {
        return mTitle;
    }
}