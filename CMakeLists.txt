cmake_minimum_required(VERSION 3.12)

project(
    Nui 
    VERSION 0.0.1
    DESCRIPTION "A Cross-Platform C++ UI framework."
    LANGUAGES CXX OBJCXX 
)

file(GLOB NuiHeaders ${CMAKE_CURRENT_SOURCE_DIR}/inc/Nui/*.h)
file(GLOB NuiSources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(
    Nui 
    SHARED 
    ${NuiHeaders}
    ${NuiSources}
)

target_include_directories(
    Nui 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/inc 
)

if (APPLE AND NOT IOS)

    find_library(
        NuiLibCocoa 
        Cocoa 
        REQUIRED
    )

    target_link_libraries(
        Nui 
        PRIVATE 
            ${NuiLibCocoa}
    )

    file(
        GLOB NuiAPPLEHeaders 
        ${CMAKE_CURRENT_SOURCE_DIR}/inc/Nui/macos/*.h 
    )
    file(
        GLOB NuiAPPLESources 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/macos/*.mm 
    )
    target_sources(
        Nui 
        PRIVATE 
            ${NuiAPPLEHeaders}
            ${NuiAPPLESources}
    )

endif () 

if (WIN32) 

    set(CMAKE_MFC_FLAG 1)

    target_compile_definitions(
        Nui 
        PRIVATE 
            -D_AFXDLL
    ) 

    file(
        GLOB NuiWINHeaders 
        ${CMAKE_CURRENT_SOURCE_DIR}/inc/Nui/win/*.h 
    )
    file(
        GLOB NuiWINSources 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/win/*.cpp
    )
    target_sources(
        Nui
        PRIVATE
            ${NuiWINHeaders}
            ${NuiWINSources}
    )

endif ()
