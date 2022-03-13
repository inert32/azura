#ifdef __linux__
    #include <unistd.h>
    #include <ncurses.h>
#else
    #include <Windows.h>
    //#include "pdcurses.h"
#endif
#include "ui_curses.h"

curses_ui::curses_ui() {
    setlocale(LC_ALL, ""); // Reset locale to print Unicode symbols
    initscr(); // Start curses library
    raw(); // Disable signal generation on Ctrl+ keys
    noecho(); // Don`t print user input on screen
    printw("Init ncurses\n");
    _test_curses();
    refresh(); // Refresh console buffer
    getch(); // Wait for user input (anykey)
}

curses_ui::~curses_ui() {
    endwin(); // Shutdown curses library
}

void curses_ui::pause() {
    msg("Press any key to continue");
}

void curses_ui::msg(const std::string& msg) {
    printw(msg.c_str());
    printw("\n");
    refresh();
    getch();
}
    
bool curses_ui::main_cycle(tourist_ctl* t) {
    msg("Called tourist_ctl*");
    return false;
}

bool curses_ui::main_cycle(tour_ctl* t){
    msg("Called tour_ctl*");
    return false;
}
bool curses_ui::main_cycle(employe_ctl* t){
    msg("Called employe_ctl*");
    return false;
}

void curses_ui::_test_curses() {
    printw("Проверка Юникода в терминале:\n");
    printw("北京 天津 \n");
    printw("日本国\n");
    printw("ᎃᎄᎅᎇ\n");
    printw("●◐◸◻\n");
    printw("ѦѨѬѰ҉\n");
    refresh();
    getch();
}
