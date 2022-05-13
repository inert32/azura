cmake_minimum_required(VERSION 3.18)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC_VERSION LESS 1910)
	message(FATAL_ERROR "This project require C++17")
endif()

project(azura_proj)

add_compile_definitions(AZ_VER_MAJOR=0)
add_compile_definitions(AZ_VER_MINOR=5)
add_compile_definitions(AZ_VER_PATCH=0)

add_executable(azura
src/main.cpp src/base.cpp src/io.cpp src/parsers.cpp src/secure.cpp
src/ui/ui_min.cpp src/locale.cpp

src/base.h src/io.h src/parsers.h src/secure.h src/db_base.h
src/ui/ui_min.h src/locale.h)

target_compile_features(azura PUBLIC cxx_std_17)

# Debug options
option (AZ_DEBUG "Debug mode" ON)
if (AZ_DEBUG OR CMAKE_BUILD_TYPE EQUAL "Debug")
    message(NOTICE "Enabled debugging build")
    set(CMAKE_BUILD_TYPE Debug)
    add_compile_definitions(AZ_DEBUG)
endif()

# Add compiler-dependeded options

if(CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(-Werror -Wpedantic -Wall)
elseif(MSVC)
    add_compile_options(/Wall /We)
    add_compile_definitions(_UNICODE)
endif()
