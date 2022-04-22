#ifndef __UI_BASE_H__
#define __UI_BASE_H__

/* Header file ui.h
   Contain all avaliable UIs:
   min_tui - based on simple console UI
   wx_gui  - wxWidgets GUI
   Note: all UI classes must be inherited from ui_ctl
*/

#include <string_view>
#include "../base.h"
#include "../db_base.h"

enum class ui_tables_list {
    tourist_t,
    tour_t,
    employe_t
};

class ui_ctl {
public:
    virtual bool login() = 0;
    virtual void get_tables(db_base<tourist_t>* a, db_base<tour_t>* b, db_base<employe_t>* c) = 0;
    virtual void main() = 0;
    
    virtual void msg(std::string_view msg) = 0;
    virtual void msg(std::string_view head, std::string_view msg) = 0;
protected:
    ui_tables_list current_table;
};

#endif /* __UI_BASE_H__ */