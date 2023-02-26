/**
 * @file NDocumentView.cpp
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "Nui/NDocumentView.h"

namespace Nui 
{
    void DocumentView::setDocument(const Shared < Document >& document) 
    {
        if (mDocument) {
            mDocument->documentWillClose();
        }
        mDocument = document;
        Shared < View > content = mDocument ? mDocument->newContentView() : nullptr;
        setContentView(content);
    }

    std::string DocumentView::title() const 
    {
        if (mDocument) {
            return mDocument->title();
        }
        return "";
    }

    void DocumentView::attached() 
    {
        if (mDocument) {
            setContentView(mDocument->newContentView());
        }
    }

    void DocumentView::detached() 
    {
        if (mDocument) {
            mDocument->documentWillClose();
            mDocument.reset();
        }
    }
}