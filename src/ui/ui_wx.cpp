// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifdef AZ_GUI_WX

#include "ui_wx.h"

IMPLEMENT_WX_THEME_SUPPORT;
wxIMPLEMENT_APP(wx_gui);

wx_gui::wx_gui() {
}
wx_gui::~wx_gui() {}

bool wx_gui::login() { return true; };

bool wx_gui::main_cycle() {return false;}
    
void wx_gui::msg(std::string_view msg) {return;}
void wx_gui::msg(std::string_view head, std::string_view msg) {return;}

bool wx_gui::OnInit() {
    wx_gui_internal *gui = new wx_gui_internal();
    gui->Show(true);
    return true;
}

wx_gui_internal::wx_gui_internal() : wxFrame(NULL, wxID_ANY, "Hello World") {
    wxMenu* file_menu = new wxMenu();
    file_menu->Append((int)wx_enums::ID_Hello, "Hello!", "hello world");
    /*file_menu->Append(wx_enums::file_new, "New File");
    file_menu->Append(wx_enums::file_open, "Open File");
    file_menu->Append(wx_enums::file_save, "Save File");*/
    file_menu->AppendSeparator();
    file_menu->Append(wxID_EXIT);
    
    wxMenuBar *menu_bar = new wxMenuBar();
    menu_bar->Append(file_menu, "File");
    SetMenuBar(menu_bar);
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    Bind(wxEVT_MENU, &wx_gui_internal::OnHello, this, (int)wx_enums::ID_Hello);
    Bind(wxEVT_MENU, &wx_gui_internal::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &wx_gui_internal::OnExit, this, wxID_EXIT);
}

void wx_gui_internal::OnExit(wxCommandEvent& event) {
    Close(true);
}

void wx_gui_internal::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void wx_gui_internal::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

#endif
