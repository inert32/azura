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
    setlocale(LC_ALL, "");
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
        init_pair(tty_colors_title_error, COLOR_GREEN, COLOR_BLACK);
    }
    else {
        init_pair(tty_colors_entry_corrupted, COLOR_BLACK, COLOR_WHITE);
        init_pair(tty_colors_entry_sel, COLOR_BLACK, COLOR_WHITE);
        init_pair(tty_colors_title, COLOR_WHITE, COLOR_BLACK);
        init_pair(tty_colors_title_error, COLOR_GREEN, COLOR_BLACK);
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
    
    mvwprintw(wnd, 1, 2, body);
    wrefresh(wnd);
    getch();
    delete w;
}

void curses_ui::msg(const std::string& body) {
    msg(body, "Message");
}

void curses_ui::err(const std::string& body, const std::string& head) {
    auto w = new curses_subwin(head, tty_colors_entry_corrupted);
    auto wnd = w->get_raw();
    
    mvwprintw(wnd, 1, 2, body);
    wrefresh(wnd);
    getch();
    delete w;
}

void curses_ui::err(const std::string& body) {
    err(body, "Message");
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
    if (!secure->need_login()) return true;

    auto window = new curses_subwin("Login");
    auto raw = window->get_raw();
    mvwprintw(raw, 2, 2, "Azura v" + std::to_string(AZ_VER_MAJOR) + "." + 
    std::to_string(AZ_VER_MINOR) + "." + std::to_string(AZ_VER_PATCH));
    mvwprintw(raw, 4, 2, AZ_LOC_TAB_ID);
    mvwprintw(raw, 8, 2, AZ_LOC_TAB_PASSWD);
    FIELD* fields[3] = { new_field(1, 20, 2, 12, 0, 0), new_field(1, 20, 6, 12, 0, 0), nullptr };
    set_field_back(fields[0], A_UNDERLINE);
    set_field_back(fields[1], A_UNDERLINE);
    FORM* form = new_form(fields);
    prep_form(form);
    mvwprintw(raw, 16, 1, "Enter: save changes | Esc: discard changes");

    db_id_t uid = -1; std::string passwd;
    bool send_away = _form_control(form, raw);
    bool correct = true;
    if (send_away) { // Save data
        try {
            std::string uid_buf(field_buffer(fields[0], 0));
            uid = std::stoull(uid_buf);
            passwd = field_buffer(fields[1], 0);
            passwd = purify_buf(passwd);
        }
        catch (const std::exception& e) {
            correct = false;
        }
    }
    // cleanup
    unpost_form(form);
    free_form(form);
    for (int i = 0; i < 3; i++) free_field(fields[i]);
    delete window;
    return correct && secure->login(uid, passwd);
}

curses_subwin::curses_subwin(const std::string& title, const int color) {
    wnd = newwin(heigth, width, start_y, start_x);
    wattron(wnd, COLOR_PAIR(color));
    box(wnd, 0, 0);
    mvwprintw(wnd, 0, 2, title);
    wattroff(wnd, COLOR_PAIR(color));
    wrefresh(wnd);
}

curses_subwin::curses_subwin(const std::string& title, size_t lines, size_t cols, size_t starty, size_t startx, const int color) {
    heigth = lines;
    width = cols;
    start_x = startx;
    start_y = starty;

    wnd = newwin(heigth, width, start_y, start_x);
    wattron(wnd, COLOR_PAIR(color));
    box(wnd, 0, 0);
    mvwprintw(wnd, 0, 2, title);
    wattroff(wnd, COLOR_PAIR(color));
    wrefresh(wnd);
}
curses_subwin::curses_subwin(const std::string& title, size_t lines, size_t cols, const int color) {
    heigth = lines;
    width = cols;
    start_x = (tty_width - cols) / 2;
    start_y = (tty_heigth - lines) / 2;

    wnd = newwin(heigth, width, start_y, start_x);
    wattron(wnd, COLOR_PAIR(color));
    box(wnd, 0, 0);
    mvwprintw(wnd, 0, 2, title);
    wattroff(wnd, COLOR_PAIR(color));
    wrefresh(wnd);
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
    for (int i = 0; i < 7; i++) werase(ui_table[i]);
    for (db_id_t i = top_id; i < tty_heigth + top_id - 2; i++) {
        auto entry = origin->record_read(i);
        if (entry == nullptr) break;
        int c = 0;
        if (entry->metadata.corrupt) c = tty_colors_entry_corrupted;
        if (entry->metadata.id == current_id) c = tty_colors_entry_sel;

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
        if (entry->metadata.id == current_id) c = tty_colors_entry_sel;

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
        if (entry->metadata.id == current_id) c = tty_colors_entry_sel;

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
bool curses_ui_main<employe_t>::create_record(unparsed_t* new_data, employe_t* old_data) {
    std::string title = (old_data == nullptr) ? AZ_LOC_MENU_ENTRY_ADD : AZ_LOC_MENU_ENTRY_EDIT;
    auto window = new curses_subwin(title);
    auto raw = window->get_raw();

    parsers<employe_t> parser;
    if (old_data != nullptr) *new_data = parser.record_to_raw(old_data);

    tablist<employe_t> tabs;
    mvwprintw(raw, 2, 2, tabs.get(0));
    FIELD* fields[6];
    for (int i = 0; i < 5; i++) {
        mvwprintw(raw, 2 + i * 2, 2, tabs.get(i));
        fields[i] = new_field(1, 20, 2 + i * 2, 12, 0, 0);
        set_field_back(fields[i], A_UNDERLINE);
        set_field_buffer(fields[i], 0, new_data->fields[i + 1].c_str());
    }
    mvwprintw(raw, 12, 2, tabs.get(6)); // Password field
    mvwprintw(raw, 14, 2, tabs.get(5)); // Role field
    fields[5] = nullptr;
    FORM* form = new_form(fields);
    prep_form(form);
    if (old_data != nullptr) mvwprintw(raw, 2, 32, new_data->fields[0]);
    mvwprintw(raw, 16, 1, "Enter: save changes | Esc: discard changes");

    roles_enum role = roles_enum::guide;

    bool run = true;
    bool send_away = false;
    mvwprintw(raw, 16, 1, "Enter: save changes | Esc: discard changes");
    mvwprintw(raw, 17, 1, "Press left or right arrow to adjust role");
    while (run) {
        mvwprintw(raw, 14, 32, role_pretty(role) + "  ");
        form_driver(form, REQ_END_LINE);
        wrefresh(raw);
        switch (int ch = getch()) {
        case KEY_UP:
            form_driver(form, REQ_PREV_FIELD); break;
        case KEY_DOWN:
            form_driver(form, REQ_NEXT_FIELD); break;
        case KEY_LEFT: {
            switch (role) {
            case roles_enum::manager:
                role = roles_enum::guide; break;
            case roles_enum::chief:
                role = roles_enum::manager; break;
            default: break;
            }
            break;
        }
        case KEY_RIGHT: {
            switch (role) {
            case roles_enum::guide:
                role = roles_enum::manager; break;
            case roles_enum::manager:
                role = roles_enum::chief; break;
            default: break;
            }
            break;
        }
        case '\n':
        case '\r':
        case KEY_ENTER:
            run = false;
            send_away = true;
            break;
        case 27: // Escape key
            run = false; break;
        case KEY_BACKSPACE:
            form_driver(form, REQ_CLR_FIELD); break;
        default: 
            form_driver(form, ch); break;
        }
        form_driver(form, REQ_VALIDATION);
    }
    
    if (send_away) // Save data
        for (int i = 0; i < 6; i++)
            new_data->fields[i + 1] = field_buffer(fields[i], 0);
    new_data->fields[5] = std::to_string((int)role);
    // cleanup
    unpost_form(form);
    free_form(form);
    for (int i = 0; i < 6; i++) free_field(fields[i]);
    delete window;
    return send_away;
}
/*
bool curses_ui_main<employe_t>::create_record(employe_t* new_data, employe_t* old_data) {
    std::string title = (old_data == nullptr) ? AZ_LOC_MENU_ENTRY_ADD : AZ_LOC_MENU_ENTRY_EDIT;
    auto window = new curses_subwin(title);
    auto raw = window->get_raw();
    mvwprintw(raw, 2, 2, AZ_LOC_TABLIST_EMPLOYE_T[0]);
    FIELD* fields[6];
    roles_enum role = roles_enum::guide;
    for (int i = 0; i < 5; i++) {
        mvwprintw(raw, 2 + (i+1) * 2, 2, AZ_LOC_TABLIST_EMPLOYE_T[i + 1]);
        fields[i] = new_field(1, 20, 2 + i * 2, 12, 0, 0);
        set_field_back(fields[i], A_UNDERLINE);
        if (old_data != nullptr) {
            switch (i) {
            case 0:
                set_field_buffer(fields[i], 0, old_data->surname.c_str());
                break;
            case 1:
                set_field_buffer(fields[i], 0, old_data->name.c_str());
                break;
            case 2:
                set_field_buffer(fields[i], 0, old_data->patronymic.c_str());
                break;
            case 3:
                set_field_buffer(fields[i], 0, std::to_string(old_data->phone_number).c_str());
                break;
            case 4:
                set_field_buffer(fields[i], 0, old_data->passwd.c_str());
                break;
            }
            role = old_data->role;
        }
    }
    fields[5] = nullptr;
    FORM* form = new_form(fields);
    prep_form(form);

    if (old_data != nullptr)
        mvwprintw(raw, 2, 32, std::to_string(old_data->metadata.id));
    mvwprintw(raw, 14, 2, AZ_LOC_TABLIST_EMPLOYE_T[6]);

    

    if (send_away) { // Save data
        for (int i = 0; i < 5; i++) {
            try {
                std::string buf(field_buffer(fields[i], 0));
                switch (i) {
                case 0:
                    new_data->surname = buf; break;
                case 1:
                    new_data->name = buf; break;
                case 2: 
                    new_data->patronymic = buf; break;
                case 3:
                    new_data->phone_number = std::stoull(buf); break;
                case 4:
                    new_data->passwd = buf; break;
                }
            }
            catch (const std::exception& e) {
                new_data->metadata.corrupt = true;
            }
        }
        new_data->role = role;
    }
    // cleanup
    unpost_form(form);
    free_form(form);
    for (int i = 0; i < 5; i++) free_field(fields[i]);
    delete window;
    return send_away;
}*/

bool _form_control(FORM* form, WINDOW* wnd) {
    bool run = true;
    bool send_away = false;
    while (run) {
        form_driver(form, REQ_END_LINE);
        wrefresh(wnd);
        switch (int ch = getch()) {
        case KEY_UP:
            form_driver(form, REQ_PREV_FIELD); break;
        case KEY_DOWN:
            form_driver(form, REQ_NEXT_FIELD); break;
        case '\n':
        case '\r':
        case KEY_ENTER:
            run = false;
            send_away = true;
            break;
        case 27: // Escape key
            run = false; break;
        case KEY_BACKSPACE:
            form_driver(form, REQ_CLR_FIELD); break;
        default: 
            form_driver(form, ch); break;
        }
        form_driver(form, REQ_VALIDATION);
    }
    return send_away;
}

bool curses_ui::adduser(io_base<employe_t>* employes) {
    auto ui = new curses_ui_main<employe_t>;
    unparsed_t reg;
    bool out = ui->create_record(&reg, nullptr);
    delete ui;
    if (out == false) return false;

    parsers<employe_t> parser;
    employe_t user;
    parser.validate(&reg, &user, false);
    prettify_records<employe_t> p;
    p.prettyify(&user);
    user.role = roles_enum::chief;
    return secure->useradd(&user);
}

#endif /* AZ_USE_CURSES_UI */
