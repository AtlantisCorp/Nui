/**
 * @file NModule.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_MODULE_H__
#define __NUI_MODULE_H__

#include "NView.h"

namespace Nui 
{
    /**
     * @brief An interface for an external module.
     * 
     * A Module can create a view upon events. Your application can define any event it wants and
     * send them to the module with the Module::send() function. ModuleManager also has a
     * send() function to send the same event to every module. The answer is a std::any that is
     * expected to be of the correct type.
     * 
     */
    class Module 
    {
    public: 
        //! @brief Returns the module's name.
        virtual std::string name() const = 0;

        //! @brief Processes an event and returns something.
        virtual std::any send(std::string_view eventName, const std::dictionnary& args = {}) = 0;
    };
}

#endif 