/**
 * @file NModuleManager.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __NUI_MODULEMANAGER_H__
#define __NUI_MODULEMANAGER_H__

#include "NModule.h"

namespace Nui 
{
    /**
     * @brief A Module Manager
     * 
     */
    class ModuleManager 
    {
        //! @brief The loaded modules.
        std::vector < Shared < Module > > mModules;

    public: 
        //! @brief Adds a module to the manager.
        void add(const Shared < Module >& module);

        //! @brief Removes a module from the manager.
        void remove(const Shared < Module >& module);

        //! @brief Sends an event to each module and calls a callback for each answer.
        template < typename Cbk > 
        void send(std::string_view eventName, const std::dictionnary& args, Cbk&& function) 
        {
            for (auto& module : mModules) {
                function(module->send(eventName, args));
            }
        }
    };
}

#endif 