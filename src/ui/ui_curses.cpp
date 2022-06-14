// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "ui.h"

#ifdef AZ_USE_CURSES_UI

unsigned int tty_heigth;
unsigned int tty_width;
unsigned int tty_heigth_subwin;
unsigned int tty_width_subwin;

int mvwprintw(WINDOW *win, int y, int x, const std::string& fmt) {
    return mvwprintw(win, y, x, fmt.c_str());
}

int wprintw(WINDOW *win, const std::string& fmt) {
    return wprintw(win, fmt.c_str());
}

curses_ui::curses_ui() {
    initscr(); // Enable ncurses
    noecho();  // Disable control symbol output to screen
    keypad(stdscr, true); // Enable F* keys
    raw(); // Send all keys directly to program
    nonl();
    // Setup colors
    if (has_colors()) {
        start_color();
        init_pair(tty_colors_entry_corrupted, COLOR_RED, COLOR_BLACK);
        init_pair(tty_colors_entry_sel, COLOR_BLACK, COLOR_WHITE);
        init_pair(tty_colors_title, COLOR_GREEN, COLOR_BLACK);
    }
    else {
        init_pair(tty_colors_entry_corrupted, COLOR_BLACK, COLOR_WHITE);
        init_pair(tty_colors_entry_sel, COLOR_BLACK, COLOR_WHITE);
        init_pair(tty_colors_title, COLOR_WHITE, COLOR_BLACK);
    }
    current = tables_list::tourists;
    tty_heigth = LINES;
    tty_width = COLS;
    tty_heigth_subwin = tty_heigth / 2;
    tty_width_subwin = 3 * tty_width / 5;
    refresh();
}

curses_ui::~curses_ui() {
    endwin();
}

void curses_ui::msg(const std::string& body, const std::string& head) {
    auto w = new curses_subwin(head);
    auto wnd = w->get_raw();
    
    mvwprintw(wnd, 1, 1, body);
    wrefresh(wnd);
    getch();
    delete w;
}

void curses_ui::msg(const std::string& body) {
    msg(body, "Message");
}

void curses_ui::main(db_base<tourist_t>* tourists, 
                     db_base<tour_t>* tours,
                     db_base<employe_t>* employes) {
    bool run = true;
    while (run) {
        switch (current) {
            case tables_list::tourists: {
                auto ui = new curses_ui_main<tourist_t>;
                ui->set_tables(tourists, tours, employes);
                current = ui->main(tourists, current);
                delete ui;
                break;
            }
            case tables_list::tours: {
                auto ui = new curses_ui_main<tour_t>;
                ui->set_tables(tourists, tours, employes);
                current = ui->main(tours, current);
                delete ui;
                break;
            }
            case tables_list::employes: {
                auto ui = new curses_ui_main<employe_t>;
                ui->set_tables(tourists, tours, employes);
                current = ui->main(employes, current);
                delete ui;
                break;
            }
            case tables_list::_quit:
                run = false;
                break;
        }
    }
}
    
bool curses_ui::login() {
    return true;
}
bool curses_ui::adduser(io_base<employe_t>* employes) {
    return false;
}

curses_subwin::curses_subwin(const std::string& title) {
    wnd = newwin(heigth, width, start_y, start_x);
    box(wnd, 0, 0);
    wattron(wnd, COLOR_PAIR(tty_colors_title));
    mvwprintw(wnd, 0, 2, title);
    wattroff(wnd, COLOR_PAIR(tty_colors_title));
    wrefresh(wnd);
}
curses_subwin::curses_subwin(const std::string& title, size_t lines, size_t cols, size_t starty, size_t startx) {
    heigth = lines;
    width = cols;
    start_x = startx;
    start_y = starty;

    wnd = newwin(heigth, width, start_y, start_x);
    wattron(wnd, COLOR_PAIR(tty_colors_title));
    box(wnd, 0, 0);
    mvwprintw(wnd, 0, 2, title);
    wrefresh(wnd);
    wattroff(wnd, COLOR_PAIR(tty_colors_title));
}

curses_subwin::~curses_subwin() {
    wclear(wnd);
    wrefresh(wnd);
    delwin(wnd);
}

WINDOW* curses_subwin::get_raw() {
    return wnd;
}
void curses_subwin::get_start_pos(size_t *y, size_t *x) {
    *y = start_y;
    *x = start_x;
}
void curses_subwin::get_size(size_t *y, size_t *x) {
    *y = heigth;
    *x = width;
}

void curses_subwin::print(const std::string& text, size_t y, size_t x) {
    mvwprintw(wnd, y, x, text);
    wrefresh(wnd);
}

template<>
unsigned int *curses_ui_main<tourist_t>::_calc_table_width() {
    unsigned int* val = new unsigned int[7];
    val[0] = 3;
    val[0] += ((tty_width - val[0]) / 6) % 7; // Enlarge id column if we have place remain
    for (int i = 1; i < 7; i++) val[i] = (tty_width - val[0]) / 6; // Make equal size columns
    return val;
}

template<>
size_t curses_ui_main<tourist_t>::_fill_tables(db_base<tourist_t>* origin) {
    size_t y_offset = 0;
    for (int i = 0; i < 7; i++) wclear(ui_table[i]);
    for (db_id_t i = top_id; i < tty_heigth + top_id - 2; i++) {
        auto entry = origin->record_read(i);
        if (entry == nullptr) break;
        int c = 0;
        if (entry->metadata.corrupt) c = tty_colors_entry_corrupted;
        else if (entry->metadata.id == current_id) c = tty_colors_entry_sel;

        if (c != 0) for (int i = 0; i < 7; i++) wattron(ui_table[i], COLOR_PAIR(c));
        mvwprintw(ui_table[0], y_offset, 0, std::to_string(entry->metadata.id));
        mvwprintw(ui_table[1], y_offset, 0, entry->surname);
        mvwprintw(ui_table[2], y_offset, 0, entry->name);
        mvwprintw(ui_table[3], y_offset, 0, entry->patronymic);
        mvwprintw(ui_table[4], y_offset, 0, std::to_string(entry->passport_series));
        mvwprintw(ui_table[5], y_offset, 0, std::to_string(entry->passport_number));
        mvwprintw(ui_table[6], y_offset, 0, phone_to_str(entry->phone_number));
        if (c != 0) for (int i = 0; i < 7; i++) wattroff(ui_table[i], COLOR_PAIR(c));
        y_offset++;
    }
    return 0;
}

template<>
void curses_ui_main<tourist_t>::_mk_tables_headers() {
    for (int i = 0; i < 7; i++) {
        wattron(ui_head[i], COLOR_PAIR(tty_colors_title));
        wprintw(ui_head[i], AZ_LOC_TABLIST_TOURIST_T[i]);
        wattroff(ui_head[i], COLOR_PAIR(tty_colors_title));
    }
}

template<>
tourist_t curses_ui_main<tourist_t>::create_record(tourist_t* old_data) {
    tourist_t rec;
    std::string title = (old_data == nullptr) ? "CrEate record" : "Edit record";
    auto window = new curses_subwin(title);
    auto raw = window->get_raw();
    wrefresh(raw);
    size_t y = 0, x = 0;
    window->get_size(&y, &x);
    FIELD* fields[8];
    for (int i = 0; i < 7; i++) {
        mvwprintw(raw, 2 + i * 2, 2, AZ_LOC_TABLIST_TOURIST_T[i]);
        fields[i] = new_field(1, 16, 2 + i * 2, 12, 0, 0);
    }
    fields[7] = nullptr;
    FORM* form = new_form(fields);
    set_form_win(form, raw);
    post_form(form);
    wrefresh(raw);
    getch();

    unpost_form(form);
    free_form(form);
    for (int i = 0; i < 8; i++) free_field(fields[i]);
    wrefresh(raw);
    delete window;
    return rec;
}

template<>
unsigned int *curses_ui_main<tour_t>::_calc_table_width() {
    unsigned int* val = new unsigned int[7];
    val[0] = 3;
    val[0] += ((tty_width - val[0]) / 6) % 7; // Enlarge id column if we have place remain
    for (int i = 1; i < 7; i++) val[i] = (tty_width - val[0]) / 6; // Make equal size columns
    return val;
}

template<>
size_t curses_ui_main<tour_t>::_fill_tables(db_base<tour_t>* origin) {
    size_t y_offset = 0;
    size_t low_border = 0;
    for (int i = 0; i < 7; i++) werase(ui_table[i]);
    for (db_id_t i = top_id; i < tty_heigth - 2; i++) {
        auto entry = origin->record_read(i);
        if (entry == nullptr) break;
        int c = 0;
        if (entry->metadata.corrupt) c = tty_colors_entry_corrupted;
        else if (entry->metadata.id == current_id) c = tty_colors_entry_sel;

        if (c != 0) for (int i = 0; i < 7; i++) wattron(ui_table[i], COLOR_PAIR(c));
        mvwprintw(ui_table[0], y_offset, 0, std::to_string(entry->metadata.id));
        mvwprintw(ui_table[1], y_offset, 0, entry->town_from);
        mvwprintw(ui_table[2], y_offset, 0, entry->town_to);
        mvwprintw(ui_table[3], y_offset, 0, entry->date_start.to_string());
        mvwprintw(ui_table[4], y_offset, 0, entry->date_end.to_string());
        mvwprintw(ui_table[5], y_offset, 0, std::to_string(entry->manager));
        const auto count = entry->tourists.size();
        low_border += count;
        for (size_t i = 0; i < count; i++) {
            mvwprintw(ui_table[6], y_offset, 0, human_to_string(tourists_ptr, entry->tourists[i]));
            if (i + 1 < count) y_offset++;
        }
        if (c != 0) for (int i = 0; i < 7; i++) wattroff(ui_table[i], COLOR_PAIR(c));
        y_offset++;
    }
    return low_border;
}

template<>
void curses_ui_main<tour_t>::_mk_tables_headers() {
    for (int i = 0; i < 7; i++) {
        wattron(ui_head[i], COLOR_PAIR(tty_colors_title));
        wprintw(ui_head[i], AZ_LOC_TABLIST_TOUR_T[i]);
        wattroff(ui_head[i], COLOR_PAIR(tty_colors_title));
    }
}

template<>
tour_t curses_ui_main<tour_t>::create_record(tour_t* old_data) {
    tour_t rec;
    return rec;
}

template<>
unsigned int *curses_ui_main<employe_t>::_calc_table_width() {
    unsigned int* val = new unsigned int[7];
    val[0] = 3;
    val[0] += ((tty_width - val[0]) / 5) % 6; // Enlarge id column if we have place remain
    for (int i = 1; i < 6; i++) val[i] = (tty_width - val[0]) / 5; // Make equal size columns
    val[6] = 0;
    return val;
}

template<>
size_t curses_ui_main<employe_t>::_fill_tables(db_base<employe_t>* origin) {
    size_t y_offset = 0;
    for (db_id_t i = top_id; i < tty_heigth - 2; i++) {
        auto entry = origin->record_read(i);
        if (entry == nullptr) break;
        int c = 0;
        if (entry->metadata.corrupt) c = tty_colors_entry_corrupted;
        else if (entry->metadata.id == current_id) c = tty_colors_entry_sel;

        if (c != 0) for (int i = 0; i < 6; i++) wattron(ui_table[i], COLOR_PAIR(c));
        mvwprintw(ui_table[0], y_offset, 0, std::to_string(entry->metadata.id));
        mvwprintw(ui_table[1], y_offset, 0, entry->surname);
        mvwprintw(ui_table[2], y_offset, 0, entry->name);
        mvwprintw(ui_table[3], y_offset, 0, entry->patronymic);
        mvwprintw(ui_table[4], y_offset, 0, std::to_string(entry->phone_number));
        mvwprintw(ui_table[5], y_offset, 0, role_pretty(entry->role));
        if (c != 0) for (int i = 0; i < 6; i++) wattroff(ui_table[i], COLOR_PAIR(c));
        y_offset++;
    }
    return 0;
}

template<>
void curses_ui_main<employe_t>::_mk_tables_headers() {
    for (int i = 0; i < 6; i++) {
        wattron(ui_head[i], COLOR_PAIR(tty_colors_title));
        wprintw(ui_head[i], AZ_LOC_TABLIST_EMPLOYE_T[i]);
        wattroff(ui_head[i], COLOR_PAIR(tty_colors_title));
    }
}

template<>
employe_t curses_ui_main<employe_t>::create_record(employe_t* old_data) {
    employe_t rec;
    return rec;
}

#endif /* AZ_USE_CURSES_UI */