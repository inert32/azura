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
        std::cout.width(5);
        if (entry->metadata.corrupt) std::cout << "!";
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

#define restore_old_value (buf == "-" && old_data != nullptr)

template<>
tourist_t min_ui_main<tourist_t>::create_record(tourist_t* old_data) {
    tourist_t tmp;
    std::string buf;
    std::cout << AZ_LOC_TAB_SURNAME << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->surname << std::endl;
        tmp.surname = old_data->surname;
    }
    else tmp.surname = buf;
    
    std::cout << AZ_LOC_TAB_NAME << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->name << std::endl;
        tmp.name = old_data->name;
    }
    else tmp.name = buf;
    
    std::cout << AZ_LOC_TAB_PATRONYMIC << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->patronymic << std::endl;
        tmp.patronymic = old_data->patronymic;
    }
    else tmp.patronymic = buf;
    
    std::cout << AZ_LOC_TAB_PASSPORT_SERIES << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->passport_series << std::endl;
        tmp.passport_series = old_data->passport_series;
    }
    else tmp.passport_series = std::stoi(buf);
    
    std::cout << AZ_LOC_TAB_PASSPORT_NUMBER << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->passport_number << std::endl;
        tmp.passport_number = old_data->passport_number;
    }
    else tmp.passport_number = std::stoi(buf);
    
    std::cout << AZ_LOC_TAB_PHONE_NUMBER << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->phone_number << std::endl;
        tmp.phone_number = old_data->phone_number;
    }
    else tmp.phone_number = str_to_phone(buf);
    prettify_records<tourist_t> pr;
    pr.prettyify(&tmp);

    return tmp;
}

template<>
tour_t min_ui_main<tour_t>::create_record(tour_t* old_data) {
    std::string buf;
    tour_t tmp;

    std::cout << AZ_LOC_TAB_TOWN_FROM << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->town_from << std::endl;
        tmp.town_from = old_data->town_from;
    }
    else tmp.town_from = buf;
    
    std::cout << AZ_LOC_TAB_TOWN_TO << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->town_to << std::endl;
        tmp.town_to = old_data->town_to;
    }
    else tmp.town_to = buf;
    
    std::cout << AZ_LOC_TAB_DATE_START << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->date_start << std::endl;
        tmp.date_start = old_data->date_start;
    }
    else tmp.date_start.set(buf);
    
    std::cout << AZ_LOC_TAB_DATE_END << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->date_end << std::endl;
        tmp.date_end = old_data->date_end;
    }
    else tmp.date_end.set(buf);
    
    std::cout << AZ_LOC_TAB_MANAGER << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->manager << std::endl;
        tmp.manager = old_data->manager;
    }
    else tmp.manager = std::stoull(buf);
    
    std::cout << "ids of tourists (divide by semicolons): ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field unchanged" << std::endl;
        tmp.tourists = old_data->tourists;
    }
    else {
        for (auto &c : buf) if (c == ',' || c == ' ') c = ';';
        parsers<tour_t> parser; 
        parser.parse_tourists_count(buf, &tmp.tourists);
    }
    prettify_records<tour_t> pr;
    pr.prettyify(&tmp);
    
    return tmp;
}

template<>
employe_t min_ui_main<employe_t>::create_record(employe_t* old_data) {
    employe_t tmp;
    std::string buf;
    std::cout << AZ_LOC_TAB_SURNAME << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->surname << std::endl;
        tmp.surname = old_data->surname;
    }
    else tmp.surname = buf;
    
    std::cout << AZ_LOC_TAB_NAME << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->name << std::endl;
        tmp.name = old_data->name;
    }
    else tmp.name = buf;
    
    std::cout << AZ_LOC_TAB_PATRONYMIC << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->patronymic << std::endl;
        tmp.patronymic = old_data->patronymic;
    }
    else tmp.patronymic = buf;
    
    std::cout << AZ_LOC_TAB_PHONE_NUMBER << ": ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->phone_number << std::endl;
        tmp.phone_number = old_data->phone_number;
    }
    else tmp.phone_number = str_to_phone(buf);

    std::cout << "Roles: 0 - (G)uide, 1 - (M)anager, 2 - (C)hief" << std::endl;
    std::cout << "Role: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << role_pretty(old_data->role) << std::endl;
        tmp.role = old_data->role;
    }
    else {
        switch (buf[0]) {
        case '1':
        case 'M':
        case 'm':
            tmp.role = roles_enum::manager; break;
        case '2':
        case 'C':
        case 'c':
            tmp.role = roles_enum::chief; break;
        default: break; // Default value - guide
        }
    }

    std::cout << AZ_LOC_TAB_PASSWD << ": ";
    std::cin >> buf;
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->passwd << std::endl;
        tmp.passwd = old_data->passwd;
    }
    else tmp.passwd = buf;
    prettify_records<employe_t> pr;
    pr.prettyify(&tmp);
    
    return tmp;
}

bool min_ui::adduser(io_base<employe_t>* employes) {
    std::cout << "Create new user: " << std::endl;
    auto ui = new min_ui_main<employe_t>;
    employe_t reg = ui->create_record();
    delete ui;
    reg.role = roles_enum::chief;
    return secure->useradd(&reg);
}

#endif /* AZ_USE_MIN_UI */
