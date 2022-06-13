#ifndef __UI_CURSES_H__
#define __UI_CURSES_H__

#include "ui.h"

#ifdef AZ_USE_CURSES_UI

extern unsigned int tty_heigth;
extern unsigned int tty_width;
extern unsigned int tty_heigth_subwin;
extern unsigned int tty_width_subwin;

enum tty_colors {
    _null,
    tty_colors_entry_sel,
    tty_colors_entry_corrupted,
    tty_colors_title
};

// std::string wrappers for ncurses API
int mvwprintw(WINDOW *win, int y, int x, const std::string& fmt);
int wprintw(WINDOW *win, const std::string& fmt);

class curses_ui : public ui_base {
public:
    curses_ui();
    ~curses_ui();

    void msg(const std::string& body);
    void msg(const std::string& body, const std::string& head);
    void main(db_base<tourist_t>* tourists, 
              db_base<tour_t>* tours,
              db_base<employe_t>* employes);
    
    bool login();
    bool adduser(io_base<employe_t>* employes);
private:
    tables_list current;
};

template<class T>
class curses_ui_main {
public:
    void set_tables(db_base<tourist_t>* tourists, db_base<tour_t>* tours, db_base<employe_t>* employes);
    tables_list main(db_base<T>* table, const tables_list current);
    T create_record(T* old_data = nullptr);

private:
    void record_create(db_base<T>* table);
    void record_update(db_base<T>* table);
    void record_delete(db_base<T>* table);
    void table_print(db_base<T>* table);

    tables_list switch_table();

    db_base<tourist_t>* tourists_ptr = nullptr;
    db_base<tour_t>* tours_ptr = nullptr;
    db_base<employe_t>* employes_ptr = nullptr;

    void _mk_tables();
    size_t _fill_tables(db_base<T>* origin);
    void _mk_tables_headers();
    unsigned int* _calc_table_width();
    WINDOW* ui_table[7] = { nullptr };
    WINDOW* ui_head[7] = { nullptr };
    db_id_t current_id = 0; // Selected entry
    db_id_t top_id = 0; // Highest enrty on screen
};

class curses_subwin {
public:
    curses_subwin(const std::string& title);
    curses_subwin(const std::string& title, size_t lines, size_t cols, size_t starty, size_t startx);
    ~curses_subwin();

    WINDOW* get_raw();

    void get_start_pos(size_t *y, size_t *x);
    void get_size(size_t *y, size_t *x);
    void print(const std::string& text, size_t y = 1, size_t x = 1);
private:
    size_t heigth = tty_heigth_subwin;
    size_t width = tty_width_subwin;
    size_t start_y = tty_heigth / 4;
    size_t start_x = tty_width / 3;
    WINDOW* wnd;
};

template<class T>
void curses_ui_main<T>::set_tables(db_base<tourist_t>* tourists, db_base<tour_t>* tours, db_base<employe_t>* employes) {
    tourists_ptr = tourists;
    tours_ptr = tours;
    employes_ptr = employes;
}

template<class T>
void curses_ui_main<T>::_mk_tables() {
    // Calculate tables width
    auto wid = _calc_table_width();
    unsigned int width_offset = 0;
    for (int i = 0; i < 7; i++) {
        delwin(ui_head[i]);
        ui_head[i] = newwin(1, wid[i], 0, width_offset);
        delwin(ui_table[i]);
        ui_table[i] = newwin(tty_heigth - 2, wid[i], 1, width_offset);
        width_offset += wid[i];
    }
    _mk_tables_headers();
}

template<class T>
tables_list curses_ui_main<T>::switch_table() {
    return tables_list::_quit;
}

template<class T>
tables_list curses_ui_main<T>::main(db_base<T>* table, const tables_list current) {
    _mk_tables();
    for (int i = 0; i < 7; i++) wnoutrefresh(ui_head[i]);
    WINDOW* actions = newwin(1, tty_width, tty_heigth - 1, 0);
    wprintw(actions, "F1 New | F2 Edit | F3 Delete | F9 Switch table | F10 Quit");
    wnoutrefresh(actions);
    while (true) {
        auto low_border = _fill_tables(table);
        for (int i = 0; i < 7; i++) wnoutrefresh(ui_table[i]);
        doupdate();
        delwin(actions);
        switch (auto c = getch())
        case KEY_F(1): {
            ui_global->msg("Create record", "Edit");
            break;
        case KEY_F(2):
            ui_global->msg("Edit record", "Edit");
            break;
        case KEY_F(3):
            ui_global->msg("Delete record", "remove");
            break;
        case KEY_UP: {
            if (current_id > 0) current_id--;
            if (current_id < top_id) top_id--;
            break;
        }
        case KEY_DOWN: {
            if (current_id < table->db_size() - 1) current_id++;
            if (current_id > top_id + tty_heigth - 3 || low_border > top_id + tty_heigth - 3) top_id++; // decrease top_id if we get below screen
            break;
        }
        case KEY_F(10):
            return tables_list::_quit;
        }
    }
    return current;
}

template<class T>
void curses_ui_main<T>::record_create(db_base<T>* table) {
    auto rec = create_record(nullptr);
    //table->record_create(&rec);
}

template<class T>
void curses_ui_main<T>::record_update(db_base<T>* table) {}

template<class T>
void curses_ui_main<T>::record_delete(db_base<T>* table) {}

#endif /* AZ_USE_CURSES_UI */

#endif /* __UI_CURSES_H__ */