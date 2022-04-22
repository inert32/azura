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

    void main();
    void get_tables(db_base<tourist_t>* a, db_base<tour_t>* b, db_base<employe_t>* c);
    
    void msg(std::string_view msg);
    void msg(std::string_view head, std::string_view msg);
private:
    bool print_menu(db_base<tourist_t>* t);
    bool print_menu(db_base<tour_t>* t);
	bool print_menu(db_base<employe_t>* t);

	void draw_table(db_base<tourist_t>* t);
	void draw_table(db_base<tour_t>* t);
	void draw_table(db_base<employe_t>* t);

    void input(db_base<tourist_t>* t);
    void input(db_base<tour_t>* t);
    void input(db_base<employe_t>* t);

    void edit(db_base<tourist_t>* t);
    void edit(db_base<tour_t>* t);
    void edit(db_base<employe_t>* t);

    void remove(db_base<tourist_t>* t);
    void remove(db_base<tour_t>* t);
    void remove(db_base<employe_t>* t);

	db_base<tourist_t>* tourists = nullptr;
	db_base<tour_t>* tours = nullptr;
	db_base<employe_t>* employes = nullptr;
};

#endif /* __UI_MIN_H__ */
