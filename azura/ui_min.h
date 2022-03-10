#ifndef __UI_MIN_H__
#define __UI_MIN_H__
/* Header file ui_min.h
   Contain UI class interface, along with minimal console UI (min_tui)

   Minimal console UI should be used only if WinAPI or *curses 
   interface unavaliable
*/

#include <iostream>
#include "base.h"

class ui_ctl {
public:
	virtual void draw_table(tourist_ctl* t) = 0;
	virtual void draw_table(tour_ctl* t) = 0;
	virtual void draw_table(employe_ctl* t) = 0;

	virtual void input(tourist_ctl* t) = 0;
	virtual void input(tour_ctl* t) = 0;
	virtual void input(employe_ctl* t) = 0;
};

class min_tui : public ui_ctl {
public:
	min_tui();
	~min_tui();

	void draw_table(tourist_ctl* t);
	void draw_table(tour_ctl* t);
	void draw_table(employe_ctl* t);

	void input(tourist_ctl* t);
	void input(tour_ctl* t);
	void input(employe_ctl* t);

	void choose(tourist_ctl* t);
	void edit(tourist_ctl* t);
	void remove(tourist_ctl* t);
};

#endif