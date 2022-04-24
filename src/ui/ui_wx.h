#ifndef __UI_WX_H__
#define __UI_WX_H__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/grid.h>
#include <wx/event.h>

#include <string_view>
#include "../locale.h"
#include "../db_base.h"

enum class ui_tables_list {
    tourist_t,
    tour_t,
    employe_t
};

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

class wx_gui_main : public wxFrame {
public:
	wx_gui_main();
	~wx_gui_main();

	void msg(std::string_view msg);
    void msg(std::string_view head, std::string_view msg);
private:
	bool init_db();

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

	bool run = false;
	ui_tables_list current_table;

    io_base<tourist_t>* tourists_io = nullptr;
    io_base<tour_t>*    tours_io    = nullptr;
    io_base<employe_t>* employes_io  = nullptr;

    db_base<tourist_t>* tourists    = nullptr;
	db_base<tour_t>*    tours       = nullptr;
	db_base<employe_t>* employes    = nullptr;
};

class wx_gui : public wxApp {
public:
	virtual bool OnInit();
};

#endif /* __UI_WX_H__ */