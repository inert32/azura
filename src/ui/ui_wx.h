#ifndef __UI_WX_H__
#define __UI_WX_H__

#ifdef AZ_GUI_WX

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/grid.h>
#include <wx/event.h>

#include <string_view>
#include "../db/tour_ctl.h"
#include "../db/tourist_ctl.h"
#include "../db/employe_ctl.h"
#include "ui_base.h"

enum class wx_enums {
	mm_swuser = 1,
	mm_swtab,

    entry_add,
	entry_edit,
	entry_remove,

	db_new,
	db_save,
	db_backup,
	db_remove,

	btn_ok,
	btn_cancel
};

class wx_gui : public ui_ctl {
public:
	wx_gui();
	~wx_gui();

	bool login();
	void main();
	void get_tables(tourist_ctl* a, tour_ctl* b, employe_ctl* c);
    
    void msg(std::string_view msg);
    void msg(std::string_view head, std::string_view msg);
};

class wx_gui_app : public wxApp {
public:
    wx_gui_app();
    ~wx_gui_app();
    
private:
    virtual bool OnInit();
};

class wx_gui_main : public wxFrame{
public:
	wx_gui_main();
	~wx_gui_main();

private:
	void init_loadmenus();

	void draw_table(wxPaintEvent& event);
	// Menus functions
	void ctl_mm_swuser(wxCommandEvent& event);
	void ctl_mm_swtab(wxCommandEvent& event);
	void ctl_exit(wxCommandEvent& event);

	void ctl_entry_add(wxCommandEvent& event);
	void ctl_entry_edit(wxCommandEvent& event);
	void ctl_entry_remove(wxCommandEvent& event);

	void ctl_db_new(wxCommandEvent& event);
	void ctl_db_save(wxCommandEvent& event);
	void ctl_db_backup(wxCommandEvent& event);
	void ctl_db_remove(wxCommandEvent& event);

	tourist_ctl* tourists = nullptr;
	tour_ctl* tours = nullptr;
	employe_ctl* employes = nullptr;
};
#endif /* AZ_GUI_WX */

#endif /* __UI_WX_H__ */
