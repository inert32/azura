cmake_minimum_required(VERSION 3.18)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC_VERSION LESS 1910)
	message(FATAL_ERROR "This project require C++17")
endif()

project(azura_proj)

add_executable(azura 
src/main.cpp src/io.cpp src/parsers.cpp 
src/db/employe_ctl.cpp src/db/tour_ctl.cpp src/db/tourist_ctl.cpp 
src/ui/ui_wx.cpp

src/base.h src/io.h src/parsers.h 
src/db/employe_ctl.h src/db/tour_ctl.h src/db/tourist_ctl.h 
src/ui/ui_min.h src/ui/ui_wx.h)

target_compile_features(azura PUBLIC cxx_std_17)

# Debug options
option (AZ_DEBUG "Debug mode" OFF)
if (AZ_DEBUG OR CMAKE_BUILD_TYPE EQUAL "Debug")
    message(NOTICE "Enabled debugging build")
    add_compile_definitions(AZ_DEBUG)
    set(AZ_DEBUG TRUE)
    if(CMAKE_COMPILER_IS_GNUCC)
        add_compile_options(-g3 -O0)
    endif()
endif()

# Setup wxWidgets UI
option (AZ_GUI_WX "Build wxWidgets UI" ON)
if (AZ_GUI_WX)
    message(NOTICE "Enabled wxWidgets UI")
    add_compile_definitions(AZ_GUI_WX)
    set(wxWidgets_USE_UNICODE TRUE)
    if (AZ_DEBUG EQUAL TRUE)
        set(wxWidgets_USE_DEBUG TRUE)
    endif()
    
    find_package(wxWidgets REQUIRED COMPONENTS core base)
    include(${wxWidgets_USE_FILE})
    target_link_libraries(azura ${wxWidgets_LIBRARIES})
endif()

if(CMAKE_COMPILER_IS_GNUCC)
	add_compile_options(-Werror -Wpedantic -Wall)
elseif(MSVC)
    add_compile_options(/Wall /We)
    add_compile_definitions(UNICODE)
    add_compile_definitions(_UNICODE)
endif()
