/**
 * @file NApplication.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Nui/NApplication.h"

class NWinApp : public CWinApp 
{

};

namespace Nui 
{
    NWinApp __globalNuiWinApp ;
    Application* __globalNApp = NULL ;

    Application::Application() 
    {
        if (__globalNApp) {
            throw std::runtime_error("Nui:Application: An instance is already running.");
        }
        __globalNApp = this; 
        mShouldTerminate = FALSE;
    }

    void Application::run() 
    {
        // first we initialize the application.
        initialize();

        // next we run the main message loop.
        MSG msg; 
        BOOL bRet; 

        while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0 && mShouldTerminate == FALSE) {
            __globalNuiWinApp.PreTranslateMessage(&msg);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Send willTerminate event
        willTerminate();
    }

    void Application::terminate() 
    {
        mShouldTerminate = TRUE;
    }

    fs::path Application::resourcePath() const 
    {
        TCHAR moduleFileName[MAX_PATH];
        GetModuleFileName(NULL, moduleFileName, MAX_PATH);
        return (fs::path(std::string(moduleFileName)).parent_path()) / "Resources";
    }
}