#ifndef __UI_BASE_H__
#define __UI_BASE_H__

/* Header file ui.h
   Contain all avaliable UIs:
   min_tui - based on simple console UI
   wx_gui  - wxWidgets GUI
   Note: all UI classes must be inherited from ui_ctl
*/

#include <string_view>
#include "../db/tour_ctl.h"
#include "../db/tourist_ctl.h"
#include "../db/employe_ctl.h"

class ui_ctl {
public:
    virtual bool ask_pass();
    
    virtual bool main_cycle(tourist_ctl* t) = 0;
    virtual bool main_cycle(tour_ctl* t) = 0;
    virtual bool main_cycle(employe_ctl* t) = 0;
    
    virtual void msg(std::string_view msg) = 0;
    virtual void msg(std::string_view head, std::string_view msg) = 0;
};

#endif
