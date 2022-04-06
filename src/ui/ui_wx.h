#ifndef __UI_WX_H__
#define __UI_WX_H__

#ifdef AZ_GUI_WX

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <string_view>
#include "../db/tour_ctl.h"
#include "../db/tourist_ctl.h"
#include "../db/employe_ctl.h"
#include "ui_base.h"

enum class wx_enums {
    ID_Hello = 1,
    file_new,
    file_open,
    file_save
};

class wx_gui : public wxApp, public ui_ctl {
public:
    wx_gui();
    ~wx_gui();
    bool login();
    bool main_cycle();
    
    void msg(std::string_view msg);
    void msg(std::string_view head, std::string_view msg);
    
private:
    virtual bool OnInit();
};

class wx_gui_internal : public wxFrame {
public: 
    wx_gui_internal();
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

#endif

#endif
