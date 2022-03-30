// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifdef AZ_GUI_WX

#include "ui_wx.h"
#include <iostream>

bool wx_gui::ask_pass() { return true; };

bool wx_gui::main_cycle(tourist_ctl* t) {return false;}
bool wx_gui::main_cycle(tour_ctl* t) {return false;}
bool wx_gui::main_cycle(employe_ctl* t) {return false;}
    
void wx_gui::msg(std::string_view msg) {return;}
void wx_gui::msg(std::string_view head, std::string_view msg) {return;}

#endif
