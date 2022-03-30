#ifndef __UI_MIN_H__
#define __UI_MIN_H__
/* Header file ui_min.h
   Contain UI class interface, along with minimal console UI (min_ui)

   Minimal console UI should be used only if WinAPI or *curses 
   interface unavaliable
*/

#include <iostream>
#include <string_view>
#include "ui_base.h"

class min_ui : public ui_ctl {
public:
    min_ui();
    ~min_ui();
    
    bool login();
    
    bool main_cycle(tourist_ctl* t);
    bool main_cycle(tour_ctl* t);
    bool main_cycle(employe_ctl* t);
    
    void msg(std::string_view msg);
    void msg(std::string_view head, std::string_view msg);
    
private:
	void draw_table(tourist_ctl* t);
	void draw_table(tour_ctl* t);
	void draw_table(employe_ctl* t);

    void input(tourist_ctl* t);
    void input(tour_ctl* t);
    void input(employe_ctl* t);

    void edit(tourist_ctl* t);
    void remove(tourist_ctl* t);
};

#endif
