/**
 * @file NDocument.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_DOCUMENT_H__
#define __NUI_DOCUMENT_H__

#include "NView.h"

namespace Nui 
{
    /**
     * @brief Describe a document that can be displayed in a DocumentView. 
     * 
     */
    class Document 
    {
        friend class DocumentView; 
        
        //! @brief The document's title.
        std::string mTitle;

    public: 
        //! @brief Constructs a new document.
        Document(void);

        //! @brief Sets the document title.
        virtual void setTitle(const std::string& title);

        //! @brief Returns the document's title.
        virtual const std::string& title() const;

        //! @brief Creates a new view corresponding to the current document.
        virtual Shared < View > newContentView(void) const = 0;

    NUI_EVENT:

        //! @brief The document is closing. Perform any savings here.
        virtual inline void documentWillClose(void) { }
    };
}

#endif 