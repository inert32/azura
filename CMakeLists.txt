cmake_minimum_required(VERSION 3.18)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC_VERSION LESS 1910)
	message(FATAL_ERROR "This project require C++17")
endif()

project(azura_proj)

add_compile_definitions(AZ_VER_MAJOR=0)
add_compile_definitions(AZ_VER_MINOR=3)
add_compile_definitions(AZ_VER_PATCH=0)

set(_AZ_WINMAIN )

add_executable(azura "${_AZ_WINMAIN}"
src/main.cpp src/io.cpp src/parsers.cpp src/secure.cpp
src/ui/ui_wx.cpp src/locale.cpp

src/base.h src/io.h src/parsers.h src/secure.h src/db_base.h
src/ui/ui_wx.h src/locale.h)

target_compile_features(azura PUBLIC cxx_std_17)

if (MSVC)
    file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/ext/include")
    file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/ext/lib")
    target_include_directories(azura PUBLIC "${PROJECT_BINARY_DIR}/ext/include")
    target_link_directories(azura PUBLIC "${PROJECT_BINARY_DIR}/ext/lib")
endif()

# Debug options
option (AZ_DEBUG "Debug mode" ON)
if (AZ_DEBUG OR CMAKE_BUILD_TYPE EQUAL "Debug")
    message(NOTICE "Enabled debugging build")
    set(CMAKE_BUILD_TYPE Debug)
    add_compile_definitions(AZ_DEBUG)
endif()

# Setup wxWidgets UI
set(wxWidgets_USE_UNICODE TRUE)
set(wxWidgets_CONFIGURATION mswu)
if(CMAKE_COMPILER_IS_GNUCC)
    if (AZ_DEBUG)
        set(wxWidgets_USE_DEBUG TRUE)
    endif()
    
    find_package(wxWidgets REQUIRED COMPONENTS core base adv)
    include(${wxWidgets_USE_FILE})
    target_link_libraries(azura ${wxWidgets_LIBRARIES})
elseif(MSVC)
    message(NOTICE "Make sure wxWidgets devel files installed to ${PROJECT_BINARY_DIR}/ext/")
    set(_AZ_WINMAIN "WIN32")
    if (AZ_DEBUG)
        set(wxWidgets_USE_DEBUG TRUE)
        target_link_libraries(azura "wxmsw31ud_core.lib")
        target_link_libraries(azura "wxbase31ud.lib")
    else()
        target_link_libraries(azura "wxmsw31u_core.lib")
        target_link_libraries(azura "wxbase31u.lib")
    endif()
    set_target_properties(azura PROPERTIES VS_USER_PROPS "${PROJECT_BINARY_DIR}/ext/wxwidgets.props")
endif()

# Add compiler-dependeded options

if(CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(-Werror -Wpedantic -Wall)
elseif(MSVC)
    add_compile_options(/Wall /We)
    add_compile_definitions(_UNICODE)
endif()
