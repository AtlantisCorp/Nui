/**
 * @file NWindow.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Nui/NWindow.h"

static const char kNuiWndClassName[] = "NWindow";
static BOOL kNuiWndClassRegistered = FALSE;

static LRESULT CALLBACK NWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

static void InitializeWndClass(void) 
{
    if (!kNuiWndClassRegistered) {
        kNuiWndClassRegistered = TRUE;

        WNDCLASS wc = { };
        wc.lpszClassName = kNuiWndClassName;
        wc.hInstance = (HINSTANCE) GetModuleHandle(NULL);
        wc.lpfnWndProc = &NWindowProc;

        RegisterClass(&wc);
    }
}

Nui::Window::Window(const Rect& frameRect, std::string_view title, const WindowStyle& style)
{
    InitializeWndClass();

    mHandle = CreateWindow(
        kNuiWndClassName,
        title.data(),
        WS_OVERLAPPEDWINDOW,
        frameRect.origin.x, frameRect.origin.y,
        frameRect.size.width, frameRect.size.height,
        NULL, 
        NULL, 
        GetModuleHandle(NULL),
        NULL);
    
    if (!mHandle) {
        throw std::runtime_error("Nui:Window: CreateWindow() failed.");
    }
}

void Nui::Window::show() 
{
    ShowWindow(mHandle, SW_SHOW);
}

void Nui::Window::close() 
{
    DestroyWindow(mHandle);
}

Nui::Rect Nui::Window::contentFrame() const 
{
    RECT frame ;
    GetWindowRect(mHandle, &frame);
    return {
        { 
            frame.left, 
            frame.top 
        }, 
        { 
            frame.right - frame.left, 
            frame.bottom - frame.top 
        }
    };
}