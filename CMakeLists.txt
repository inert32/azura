cmake_minimum_required(VERSION 3.18)

project(azura_proj)

add_executable(azura 
src/main.cpp src/io.cpp src/parsers.cpp 
src/db/employe_ctl.cpp src/db/tour_ctl.cpp src/db/tourist_ctl.cpp 
src/ui/ui_min.cpp src/ui/ui_curses.cpp src/ui/ui_win.cpp

src/base.h src/io.h src/parsers.h 
src/db/employe_ctl.h src/db/tour_ctl.h src/db/tourist_ctl.h 
src/ui/ui_min.h src/ui/ui_curses.h src/ui/ui_win.h)

target_compile_features(azura PUBLIC cxx_std_17)

if(CMAKE_COMPILER_IS_GNUCC)
    target_link_libraries(azura stdc++fs)
    find_package(Curses REQUIRED)
    if (${CURSES_FOUND})
        target_link_libraries(azura ${CURSES_LIBRARIES})
        include_directories(${CURSES_INCLUDE_DIR})
    endif()    
	add_compile_options(-Werror -Wpedantic)
endif()
