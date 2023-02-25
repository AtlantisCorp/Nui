/**
 * @file NSearchField.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_SEARCHFIELD_H__
#define __NUI_SEARCHFIELD_H__

#include "NTextEdit.h"

namespace Nui
{
    /**
     * @brief A SearchField based on TextEdit.
     * 
     */
    class SearchField : public TextEdit 
    {
    public:
        //! @brief Constructs a new SearchField.
        SearchField(void);
    };
}

#endif // !__NUI_SEARCHFIELD_H__