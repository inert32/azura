#ifndef __UI_CURSES_H__
#define __UI_CURSES_H__

#include "ui_base.h"

class curses_ui : public ui_ctl {
public:
    curses_ui();
    ~curses_ui();
    void pause();
    void msg(const std::string& msg);
    
    bool main_cycle(tourist_ctl* t);
    bool main_cycle(tour_ctl* t);
    bool main_cycle(employe_ctl* t);
    
private:
    void _test_curses();
};

#endif
