#ifndef __UI_WX_H__
#define __UI_WX_H__

#ifdef AZ_GUI_WX

#include <wx/wxprec.h>

#include <string_view>
#include "../db/tour_ctl.h"
#include "../db/tourist_ctl.h"
#include "../db/employe_ctl.h"

class wx_gui : public ui_ctl, public wxApp {
public:
    wx_gui();
    ~wx_gui();
    bool ask_pass();
    
    bool main_cycle(tourist_ctl* t);
    bool main_cycle(tour_ctl* t);
    bool main_cycle(employe_ctl* t);
    
    void msg(std::string_view msg);
    void msg(std::string_view head, std::string_view msg);
};

#endif

#endif
