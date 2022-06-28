// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "ui.h"

#ifdef AZ_USE_MIN_UI

void _clean_input_buffer() {
	std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

min_ui::min_ui() {
    std::cout << "Azura v" << AZ_VER_MAJOR << '.' << AZ_VER_MINOR << '.' << AZ_VER_PATCH << std::endl;
    current = tables_list::tours;
    #ifdef _WIN32
    std::locale::global("Russian_Russia.1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    #endif
}

void min_ui::msg(const std::string& body) {
    std::cout << body << std::endl;
}
void min_ui::msg(const std::string& body, const std::string& head) {
    std::cout << head << std::endl << body << std::endl;
}

void min_ui::err(const std::string& body) {
    std::cerr << body << std::endl;
}
void min_ui::err(const std::string& body, const std::string& head) {
    std::cerr << head << std::endl << body << std::endl;
}

void min_ui::main(db_base<tourist_t>* tourists, db_base<tour_t>* tours, db_base<employe_t>* employes) {
    bool run = true;
    while (run) {
        switch (current) {
            case tables_list::tourists: {
                auto ui = new min_ui_main<tourist_t>;
                ui->set_tables(tourists, tours, employes);
                current = ui->main(tourists, current);
                delete ui;
                break;
            }
            case tables_list::tours: {
                auto ui = new min_ui_main<tour_t>;
                ui->set_tables(tourists, tours, employes);
                current = ui->main(tours, current);
                delete ui;
                break;
            }
            case tables_list::employes: {
                auto ui = new min_ui_main<employe_t>;
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

bool min_ui::login() {
    if (!secure->need_login()) return true;
    std::string input;
    db_id_t new_uid;

    std::cout << "Enter your ID: ";
    std::cin >> input;
    try {
        new_uid = std::stoull(input);
    }
    catch (const std::exception& e) {
        std::cout << "Not an UID." << std::endl;
        return false;
    }
    std::cout << "Enter your password: ";
    std::cin >> input;
    return secure->login(new_uid, input);
}

template<>
void min_ui_main<tourist_t>::table_print(db_base<tourist_t>* table) {
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    int align[] = { 5, 16, 16, 16, 16, 16, 22 };
    for (int i = 0; i < 7; i++) {
        std::cout.width(align[i]); std::cout << AZ_LOC_TABLIST_TOURIST_T[i];
    }
    std::cout << std::endl;
    db_id_t max = table->db_size();
    for (db_id_t i = 0; i < max; i++) {
        auto entry = table->record_read(i);
        if (!(entry->metadata.allow && entry->metadata.show)) continue;
        std::cout.width(5);
        if (entry->metadata.corrupt) std::cout << "!";
        std::cout << entry->metadata.id;
        std::cout.width(16); std::cout << entry->surname;
        std::cout.width(16); std::cout << entry->name;
        std::cout.width(16); std::cout << entry->patronymic;
        std::cout.width(16); std::cout << entry->passport_series;
        std::cout.width(16); std::cout << entry->passport_number;
        std::cout.width(22); std::cout << phone_to_str(entry->phone_number) << std::endl;
    }
}

template<>
void min_ui_main<tour_t>::table_print(db_base<tour_t>* table) {
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    int align[] = { 5, 16, 16, 12, 12, 32, 8 };
    for (int i = 0; i < 7; i++) {
        std::cout.width(align[i]); std::cout << AZ_LOC_TABLIST_TOUR_T[i];
    }
    std::cout << std::endl;
    db_id_t max = table->db_size();
    for (db_id_t i = 0; i < max; i++) {
        std::cout.setf(std::ios::left, std::ios::adjustfield);
        auto entry = table->record_read(i);
        if (!(entry->metadata.allow && entry->metadata.show)) continue;
        if (entry->metadata.corrupt) std::cout << "!";
        std::cout.width(5);
        std::cout << entry->metadata.id;
        std::cout.width(16); std::cout << entry->town_from;
        std::cout.width(16); std::cout << entry->town_to;
        std::cout.width(12); std::cout << entry->date_start;
        std::cout.width(12); std::cout << entry->date_end;
        std::cout.width(32); std::cout << human_to_string(employes_ptr, entry->manager);
        
        const auto width = 93;
        const auto count = entry->tourists.size();
        //std::cout.setf(std::ios::right, std::ios::adjustfield);
        for (size_t i = 0; i < count; i++) {
            if (i > 0) {
                std::cout << std::endl;
                for (int i = 0; i < width; i++) std::cout << ' ';
            }
            std::cout << human_to_string(tourists_ptr, entry->tourists[i]);
        }
        std::cout << std::endl;
    }
}

template<>
void min_ui_main<employe_t>::table_print(db_base<employe_t>* table) {
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    int align[] = { 5, 16, 16, 16, 20, 8 };
    for (int i = 0; i < 6; i++) {
        std::cout.width(align[i]); std::cout << AZ_LOC_TABLIST_EMPLOYE_T[i];
    }
    std::cout << std::endl;
    db_id_t max = table->db_size();
    for (db_id_t i = 0; i < max; i++) {
        auto entry = table->record_read(i);
        if (!(entry->metadata.allow && entry->metadata.show)) continue;
        std::cout.width(5);
        if (entry->metadata.corrupt) std::cout << "!";
        std::cout << entry->metadata.id;
        std::cout.width(16); std::cout << entry->surname;
        std::cout.width(16); std::cout << entry->name;
        std::cout.width(16); std::cout << entry->patronymic;
        std::cout.width(20); std::cout << phone_to_str(entry->phone_number);
        std::cout.width(8); std::cout << role_pretty(entry->role) << std::endl;
    }
}

template<>
unparsed_t min_ui_main<employe_t>::create_record(employe_t* old_data) {
    unparsed_t raw;
    parsers<employe_t> parser;
    tablist<employe_t> tabs;
    if (old_data != nullptr) raw = parser.record_to_raw(old_data);

    for (int i = 1; i < 7; i++) {
        std::string buf;
        if (i != 5) std::cout << tabs.get(i) << ": ";
        else std::cout << "Roles: 0 - (G)uide, 1 - (M)anager, 2 - (C)hief: ";
        std::getline(std::cin, buf);
        if (buf != "-") raw.fields[i] = buf;
    }

    return raw;
}


bool min_ui::adduser() {
    std::cout << "Create new user: " << std::endl;
    auto ui = new min_ui_main<employe_t>;
    auto reg = ui->create_record();
    delete ui;

    auto parser = new parsers<employe_t>;
    employe_t user;
    parser->validate(&reg, &user, false);
    delete parser;
    user.role = roles_enum::chief;
    return secure->useradd(&user);
}

#endif /* AZ_USE_MIN_UI */
