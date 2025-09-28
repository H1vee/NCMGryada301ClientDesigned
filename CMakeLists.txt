cmake_minimum_required(VERSION 3.16)

project(NCMGryada301Client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

add_compile_definitions(
    QT_NO_DEBUG_OUTPUT
    QT_NO_WARNING_OUTPUT
    QT_NO_ACCESSIBILITY
    QT_NO_CONCURRENT
    QT_NO_SQL
    QT_NO_XML
    QT_NO_MULTIMEDIA
    QT_NO_STYLE_FUSION
    QT_NO_STYLE_WINDOWS
)

if(WIN32)
    set(PLATFORM_NAME "Windows")
    add_compile_definitions(PLATFORM_WINDOWS)
elseif(APPLE)
    set(PLATFORM_NAME "macOS")
    add_compile_definitions(PLATFORM_MACOS OS_NIX OS_MAC)
    set(CMAKE_MACOSX_RPATH ON)
elseif(UNIX)
    set(PLATFORM_NAME "Linux")
    add_compile_definitions(PLATFORM_LINUX OS_NIX)
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

if(APPLE)
    find_library(OPENGL_LIBRARY OpenGL REQUIRED)
    if(NOT OPENGL_LIBRARY)
        message(FATAL_ERROR "OpenGL framework not found on macOS")
    endif()
endif()


set(CORE_SOURCES
        main.cpp
        mainwindow.cpp
        login.cpp
        changepassword.cpp
        clientsecurity.cpp
        inputvalidator.cpp
        moduleparamsdialog.cpp
        processstatedialog.cpp
        tlistitem.cpp
)

set(SETTINGS_SOURCES
        Settings/CommonSettings.cpp
        Settings/NCMsList.cpp
)

set(CRYPTO_SOURCES
        Gryada301.cpp
        CSPBase.cpp
        CSP.cpp
        CSPI.cpp
        CSPIBase.cpp
        CSPParameters.cpp
        CSPIParameters.cpp
        ICSPI.cpp
        UCSPHasher.cpp
)

set(UTILITY_SOURCES
        QRCode.cpp
        NCHostCP.cpp
        NCRemoteControlCP.cpp
)


set(PLATFORM_SOURCES)
set(PLATFORM_HEADERS)

if(WIN32)
    list(APPEND PLATFORM_SOURCES StringCoder.cpp)
    list(APPEND PLATFORM_HEADERS StringCoder.h)
endif()

set(ALL_SOURCES
        ${CORE_SOURCES}
        ${SETTINGS_SOURCES}
        ${CRYPTO_SOURCES}
        ${UTILITY_SOURCES}
        ${PLATFORM_SOURCES}
)


set(CORE_HEADERS
        mainwindow.h
        login.h
        changepassword.h
        clientsecurity.h
        inputvalidator.h
        moduleparamsdialog.h
        processstatedialog.h
        tlistitem.h
)

set(SETTINGS_HEADERS
        Settings/CommonSettings.h
        Settings/NCMsList.h
)

set(CRYPTO_HEADERS
        Gryada301.h
        CSPBase.h
        CSP.h
        CSPI.h
        CSPIBase.h
        CSPIDefines.h
        CSPDefines.h
        CSPParameters.h
        CSPIParameters.h
        ICSPIHardware.h
        ICSPHardwareRNG.h
        ICSPI.h
        ICSPIHardwareRNG.h
        UCSPHasher.h
)

set(UTILITY_HEADERS
        OSIntermediate/OSIntermediate.h
        IQRCode.h
        QRCode.h
        NCHostCP.h
        NCRemoteControlCP.h
)

set(ALL_HEADERS
        ${CORE_HEADERS}
        ${SETTINGS_HEADERS}
        ${CRYPTO_HEADERS}
        ${UTILITY_HEADERS}
        ${PLATFORM_HEADERS}
)

set(UI_FORMS
        changepassword.ui
        clientsecurity.ui
        login.ui
        mainwindow.ui
        moduleparamsdialog.ui
)

set(RESOURCES
        images.qrc
)

qt_add_resources(GENERATED_RESOURCES ${RESOURCES})


set(PLATFORM_LIBRARIES)
set(PLATFORM_LINK_DIRECTORIES)
set(PLATFORM_INCLUDE_DIRS)

if(WIN32)

    set(PLATFORM_LIBRARIES user32 advapi32 ws2_32 oleaut32)


    set(APP_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/app_icon.rc")
    set(WINDOWS_MANIFEST "${CMAKE_CURRENT_SOURCE_DIR}/admin_manifest.rc")


    if(NOT EXISTS ${APP_ICON_RESOURCE})
        message(WARNING "Windows icon resource not found: ${APP_ICON_RESOURCE}")
        set(APP_ICON_RESOURCE)
    endif()

    if(NOT EXISTS ${WINDOWS_MANIFEST})
        message(WARNING "Windows manifest not found: ${WINDOWS_MANIFEST}")
        set(WINDOWS_MANIFEST)
    endif()

elseif(APPLE)
    file(GLOB MAC_DYLIBS "${CMAKE_CURRENT_SOURCE_DIR}/MAC/64/*.dylib")

    if(NOT MAC_DYLIBS)
        message(WARNING "No dylib files found in MAC/64/ directory")
    endif()

    set(PLATFORM_LIBRARIES ${MAC_DYLIBS} ${OPENGL_LIBRARY})


    set(OPENGL_INCLUDE_DIR "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/OpenGL.framework/Headers")
    if(EXISTS ${OPENGL_INCLUDE_DIR})
        list(APPEND PLATFORM_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
    endif()

elseif(UNIX)

    set(PLATFORM_LIBRARIES osi)
    list(APPEND PLATFORM_LINK_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/64")

    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/64")
        message(WARNING "Linux library directory not found: ${CMAKE_CURRENT_SOURCE_DIR}/64")
    endif()
endif()


if(WIN32)
    qt_add_executable(${PROJECT_NAME} WIN32
            ${ALL_SOURCES}
            ${ALL_HEADERS}
            ${UI_FORMS}
            ${GENERATED_RESOURCES}
            ${WINDOWS_MANIFEST}
            ${APP_ICON_RESOURCE}
    )

    if(MSVC)
        set_target_properties(${PROJECT_NAME} PROPERTIES
                LINK_FLAGS "/MANIFEST:NO"
                WIN32_EXECUTABLE TRUE
        )
    endif()

elseif(APPLE)
    qt_add_executable(${PROJECT_NAME} MACOSX_BUNDLE
            ${ALL_SOURCES}
            ${ALL_HEADERS}
            ${UI_FORMS}
            ${GENERATED_RESOURCES}
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES
            OUTPUT_NAME "IITNCMGryada301.Client"
    )

else()
    # Linux
    qt_add_executable(${PROJECT_NAME}
            ${ALL_SOURCES}
            ${ALL_HEADERS}
            ${UI_FORMS}
            ${GENERATED_RESOURCES}
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Settings
        ${CMAKE_CURRENT_SOURCE_DIR}/OSIntermediate
        ${PLATFORM_INCLUDE_DIRS}
)

if(PLATFORM_LINK_DIRECTORIES)
    target_link_directories(${PROJECT_NAME} PRIVATE ${PLATFORM_LINK_DIRECTORIES})
endif()


target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        ${PLATFORM_LIBRARIES}
)


message(STATUS "")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Platform: ${PLATFORM_NAME}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Qt6 Version: ${Qt6_VERSION}")
message(STATUS "")