/**
 * @file NDocumentView.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_DOCUMENTVIEW_H__
#define __NUI_DOCUMENTVIEW_H__

#include "NDocument.h"
#include "NScrollView.h"

namespace Nui 
{
    /**
     * @brief A view that displays in a ScrollView a document's content view.
     * 
     */
    class DocumentView : public ScrollView 
    {
        //! @brief The document.
        Shared < Document > mDocument;

    public: 

        //! @brief Creates a new document view.
        DocumentView(void) = default;

        //! @brief Returns the current document.
        virtual inline Shared < Document > document() const { return mDocument; }

        //! @brief Sets the current document.
        virtual void setDocument(const Shared < Document >& document);

        //! @brief Returns the document's title.
        virtual std::string title() const;

    NUI_EVENT:

        //! @brief When the view is attached, it calls Document::newContentView() and 
        //! uses this view as the ScrollView content.
        virtual void attached(void);

        //! @brief Handles a documentWillClose() event, which may occurs when the view is
        //! removed from its parent.
        virtual void detached(void);
    };
}

#endif 