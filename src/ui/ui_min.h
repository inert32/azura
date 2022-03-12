#ifndef __UI_MIN_H__
#define __UI_MIN_H__
/* Header file ui_min.h
   Contain UI class interface, along with minimal console UI (min_tui)

   Minimal console UI should be used only if WinAPI or *curses 
   interface unavaliable
*/

#include <iostream>
#include <string>
#include "ui_base.h"

class min_tui : public ui_ctl {
public:
    min_tui();
    ~min_tui();
    
    bool main_cycle(tourist_ctl* t);
    bool main_cycle(tour_ctl* t);
    bool main_cycle(employe_ctl* t);

    void draw_table(tourist_ctl* t);
    void draw_table(tour_ctl* t);
    void draw_table(employe_ctl* t);

    void input(tourist_ctl* t);
    void input(tour_ctl* t);
    void input(employe_ctl* t);

    void edit(tourist_ctl* t);
    void remove(tourist_ctl* t);

	void pause();
	void msg(const std::string& msg);
};

#endif
