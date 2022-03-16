#ifndef __UI_BASE_H__
#define __UI_BASE_H__

/* Header file ui.h
   Contain all avaliable UIs:
   min_tui - based on simple console UI
   curses_ui - *curses console UI
   win_ui - Windows-only graphical UI
*/

#include "../db/tour_ctl.h"
#include "../db/tourist_ctl.h"
#include "../db/employe_ctl.h"

class ui_ctl {
public:
    virtual bool ask_pass();
    
    virtual bool main_cycle(tourist_ctl* t) = 0;
    virtual bool main_cycle(tour_ctl* t) = 0;
    virtual bool main_cycle(employe_ctl* t) = 0;
};

#endif
