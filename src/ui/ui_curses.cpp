#ifdef __linux__
    #include <unistd.h>
    #include <ncurses.h>
#else
    #include <Windows.h>
    //#include "pdcurses.h"
#endif
#include "ui_curses.h"

curses_ui::curses_ui() {/*
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
*/}

curses_ui::~curses_ui() {
   // endwin();
}

void curses_ui::pause() {
}

void curses_ui::msg(const std::string& msg) {
	//std::cout << msg << std::endl;
}

bool main_cycle(tourist_ctl* t) { return false; }
bool main_cycle(tour_ctl* t) { return false; }
bool main_cycle(employe_ctl* t) { return false; }

