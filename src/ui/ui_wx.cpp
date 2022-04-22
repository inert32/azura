// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifdef AZ_GUI_WX

#include "ui_wx.h"
#include "../locale.h"

wx_gui::wx_gui() {}

wx_gui::~wx_gui() {}

bool wx_gui_app::OnInit() {
	auto* wnd = new wx_gui_main();
	wnd->Show(true);
	return true;
}

wx_gui_app::~wx_gui_app() {
}

bool wx_gui::login() { return true; };

void wx_gui::msg(std::string_view msg) {
	wxMessageBox(msg.data(), "Notice", wxOK | wxICON_INFORMATION);
}
void wx_gui::msg(std::string_view head, std::string_view msg) {
	wxMessageBox(msg.data(), head.data(), wxOK | wxICON_INFORMATION);
}

wx_gui_main::wx_gui_main() 
	: wxFrame(NULL, wxID_ANY, AZ_LOC_PROGNAME, wxPoint(100,100), wxSize(800,600)) {

	Bind(wxEVT_PAINT, &wx_gui_main::draw_table, this, -1);

	init_loadmenus();
	CreateStatusBar();
}

void wx_gui_main::init_loadmenus() {
	wxMenu* main_menu = new wxMenu();
	main_menu->Append((int)wx_enums::mm_swuser, AZ_LOC_MENU_MM_SWUSER);
	main_menu->Append((int)wx_enums::mm_swtab, AZ_LOC_MENU_MM_SWTAB);
	main_menu->Append(wxID_EXIT, AZ_LOC_MENU_MM_QUIT);
	Bind(wxEVT_MENU, &wx_gui_main::ctl_mm_swuser, this, (int)wx_enums::mm_swuser);
	Bind(wxEVT_MENU, &wx_gui_main::ctl_mm_swtab, this, (int)wx_enums::mm_swtab);
	Bind(wxEVT_MENU, &wx_gui_main::ctl_exit, this, wxID_EXIT);

	wxMenu* db_menu = new wxMenu();
	db_menu->Append((int)wx_enums::db_new, AZ_LOC_MENU_DB_NEW);
	db_menu->Append((int)wx_enums::db_save, AZ_LOC_MENU_DB_SAVE);
	db_menu->Append((int)wx_enums::db_remove, AZ_LOC_MENU_DB_REMOVE);
	db_menu->Append((int)wx_enums::db_backup, AZ_LOC_MENU_DB_BACKUP);
	Bind(wxEVT_MENU, &wx_gui_main::ctl_db_new, this, (int)wx_enums::db_new);
	Bind(wxEVT_MENU, &wx_gui_main::ctl_db_save, this, (int)wx_enums::db_save);
	Bind(wxEVT_MENU, &wx_gui_main::ctl_db_backup, this, (int)wx_enums::db_backup);
	Bind(wxEVT_MENU, &wx_gui_main::ctl_db_remove, this, (int)wx_enums::db_remove);

	wxMenu* entry_menu = new wxMenu();
	entry_menu->Append((int)wx_enums::entry_add, AZ_LOC_MENU_ENTRY_ADD);
	entry_menu->Append((int)wx_enums::entry_edit, AZ_LOC_MENU_ENTRY_EDIT);
	entry_menu->Append((int)wx_enums::entry_remove, AZ_LOC_MENU_ENTRY_REMOVE);
	Bind(wxEVT_MENU, &wx_gui_main::ctl_entry_add, this, (int)wx_enums::entry_add);
	Bind(wxEVT_MENU, &wx_gui_main::ctl_entry_edit, this, (int)wx_enums::entry_edit);
	Bind(wxEVT_MENU, &wx_gui_main::ctl_entry_remove, this, (int)wx_enums::entry_remove);

	wxMenuBar *menu_bar = new wxMenuBar();
	menu_bar->Append(main_menu, AZ_LOC_MENU_MM);
	menu_bar->Append(db_menu, AZ_LOC_MENU_DB);
	menu_bar->Append(entry_menu, AZ_LOC_MENU_ENTRY);
	SetMenuBar(menu_bar);
}

void wx_gui_main::draw_table(wxPaintEvent& event) {
	auto grid = new wxGrid(this, -1, wxPoint(0,0), wxSize(800,600));
	grid->CreateGrid(tourists->db_size(), 7);
	grid->HideRowLabels();
	grid->SetColLabelValue(0, AZ_LOC_TAB_ID);
	grid->SetColLabelValue(1, AZ_LOC_TAB_SURNAME);
	grid->SetColLabelValue(2, AZ_LOC_TAB_NAME);
	grid->SetColLabelValue(3, AZ_LOC_TAB_PATRONYMIC);
	grid->SetColLabelValue(4, AZ_LOC_TAB_PASSPORT_NUMBER);
	grid->SetColLabelValue(5, AZ_LOC_TAB_PASSPORT_SERIES);
	grid->SetColLabelValue(6, AZ_LOC_TAB_PHONE_NUMBER);

	db_id_t max = tourists->db_size();
	for (db_id_t i = 0; i < max; i++) {
		auto v = tourists->record_get(i);
		grid->AppendRows(i);
		grid->SetCellValue(i, 0, std::to_string(v->metadata.id));
		grid->SetReadOnly(i, 0, true);
		grid->SetCellValue(i, 1, v->surname);
		grid->SetCellValue(i, 2, v->name);
		grid->SetCellValue(i, 3, v->patronymic);
		grid->SetCellValue(i, 4, std::to_string(v->passport_series));
		grid->SetCellValue(i, 5, std::to_string(v->passport_number));
		grid->SetCellValue(i, 6, std::to_string(v->phone_number));
	}
	grid->AutoSize();
}

// Menu functions

void wx_gui_main::ctl_mm_swuser(wxCommandEvent& event) {}

void wx_gui_main::ctl_mm_swtab(wxCommandEvent& event) {
	wxMessageBox("Switch table", "will switch table", wxOK | wxICON_INFORMATION);
}

void wx_gui_main::ctl_exit(wxCommandEvent& event) {
	Close(true);
}

void wx_gui_main::ctl_entry_add(wxCommandEvent& event) {
	tourist_t t;
	//auto wnd = wx_gui_subwindow(this, wx_enums::entry_add, &t);
}

void wx_gui_main::ctl_entry_edit(wxCommandEvent& event) {
	auto x = tourists->record_get(0);
	wxMessageBox(x->surname, "will edit entry", wxOK | wxICON_INFORMATION);
}

void wx_gui_main::ctl_entry_remove(wxCommandEvent& event) {
	auto x = tourists->record_get(0);
	wxMessageBox(x->patronymic, "will delete entry", wxOK | wxICON_INFORMATION);
}

void wx_gui_main::ctl_db_new(wxCommandEvent& event) {}

void wx_gui_main::ctl_db_save(wxCommandEvent& event) {}

void wx_gui_main::ctl_db_remove(wxCommandEvent& event) {}

void wx_gui_main::ctl_db_backup(wxCommandEvent& event) {}

/*
wx_gui_subwindow::wx_gui_subwindow(wxWindow* parent, const wx_enums job, tourist_t* ptr) {
	if (!(job == wx_enums::entry_add ||
		job == wx_enums::entry_edit ||
		job == wx_enums::entry_remove)) return;
	ptr_tourist_t = ptr;
	auto wnd = new wxWindow(parent, wxID_ANY, wxPoint(120, 120), wxSize(400, 400), 0, "Addd");
	button_ok = new wxButton(wnd, (int)wx_enums::btn_ok, "OK", wxPoint(320, 320));
	button_cancel = new wxButton(wnd, (int)wx_enums::btn_cancel, "Cancel", wxPoint(370, 320));

	Bind(wxEVT_BUTTON, &wx_gui_subwindow::btn_ok, this, -1);
	Bind(wxEVT_BUTTON, &wx_gui_subwindow::btn_cancel, this, -1);

	texts[0] = new wxStaticText(wnd, wxID_ANY, "Surname", wxPoint(140, 140), wxSize(10, 1), 0, "null");
	wnd->Show();
}

void wx_gui_subwindow::btn_ok(wxCommandEvent& event) {
	wxMessageBox("Added", "will switch table", wxOK | wxICON_INFORMATION);
	Close(true);
}
void wx_gui_subwindow::btn_cancel(wxCommandEvent& event) {
	Close(true);
}*/

#endif
