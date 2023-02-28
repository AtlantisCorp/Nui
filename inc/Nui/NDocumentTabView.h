/**
 * @file NDocumentTabView.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-28
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_DOCUMENTTABVIEW_H__
#define __NUI_DOCUMENTTABVIEW_H__

#include "Nui/NDocument.h"
#include "Nui/NTabView.h"

namespace Nui 
{
    /**
     *  @brief A TabView that manages a list of Documents.
     *
     *  The documents are inserted through insertDocument(), appendDocument() or prependDocument().
     *  The DocumentView is loaded only when the TabBarItem is first selected. newContentView() is
     *  called with the item index (which is the Document index in the Document's list).
     *
     *  When an item is closing, it calls the document's canCloseNow() method to see if it can
     *  close its view.
     *
     */
    class DocumentTabView : public TabView
    {
        //! @brief The documents.
        std::vector < Shared < Document > > mDocuments;
        
    public:
        
        //! @brief Inserts a new document.
        virtual void insertDocument(size_t index, const Shared < Document >& document);
        
        //! @brief Appends a new document.
        inline void appendDocument(const Shared < Document >& document)
        {
            insertDocument(mDocuments.size(), document);
        }
        
        //! @brief Prepends a new document.
        inline void prependDocument(const Shared < Document >& document)
        {
            insertDocument(0, document);
        }
        
        //! @brief Removes a document as if it was closed.
        virtual void closeDocument(const Shared < Document >& document);
        
        //! @brief Returns the document at given index.
        virtual Shared < Document > documentAt(size_t index) const;
        
        //! @brief Returns all the documents.
        inline auto const& documents() const { return mDocuments; }
        
        //! @brief Returns the selected document.
        Shared < Document > selectedDocument() const;
        
    protected:
        
        //! @brief Calls newContentView() on the nth document.
        virtual Shared < View > newContentView(size_t index) const;
    };
}

#endif 
