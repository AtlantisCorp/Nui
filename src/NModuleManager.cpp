/**
 * @file NModuleManager.cpp
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "Nui/NModuleManager.h"

void Nui::ModuleManager::add(const Shared < Module >& module) 
{
    if (std::find(mModules.begin(), mModules.end(), module) == mModules.end()) {
        mModules.push_back(module);
    }
}

void Nui::ModuleManager::remove(const Shared < Module >& module) 
{
    std::erase(mModules, module);
}