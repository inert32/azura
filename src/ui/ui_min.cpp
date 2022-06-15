// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "ui.h"

#ifdef AZ_USE_MIN_UI

void _clean_input_buffer() {
	std::cin.seekg(0, std::ios::end);
	std::cin.clear();
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
    std::cout << "id" << '\t'
              << "Surname" << '\t'
              << "Name" << '\t'
              << "Patronymic" << '\t'
              << "Passport series" << '\t'
              << "Passport number" << '\t'
              << "Phone number" << std::endl;
    db_id_t max = table->db_size();
    for (db_id_t i = 0; i < max; i++) {
        auto entry = table->record_read(i);
        if (!(entry->metadata.allow && entry->metadata.show)) continue;
        if (entry->metadata.corrupt) std::cout << "!";
        std::cout << entry->metadata.id << '\t'
                  << entry->surname << '\t'
                  << entry->name << '\t'
                  << entry->patronymic << '\t'
                  << entry->passport_series << "\t\t"
                  << entry->passport_number << "\t\t"
                  << phone_to_str(entry->phone_number) << std::endl;
    }
}

template<>
void min_ui_main<tour_t>::table_print(db_base<tour_t>* table) {
    std::cout << "id" << '\t'
              << "From" << '\t'
              << "To" << '\t'
              << "Start date" << '\t'
              << "End date" << '\t'
              << "Manager" << '\t'
              << "Tourists" << std::endl;
    db_id_t max = table->db_size();
    for (db_id_t i = 0; i < max; i++) {
        auto entry = table->record_read(i);
        if (!(entry->metadata.allow && entry->metadata.show)) continue;
        if (entry->metadata.corrupt) std::cout << "!";
        std::cout << entry->metadata.id << '\t'
                  << entry->town_from << '\t'
                  << entry->town_to << '\t'
                  << entry->date_start << '\t'
                  << entry->date_end << '\t'
                  << human_to_string(employes_ptr, entry->manager);
        
        const auto count = entry->tourists.size();
        for (size_t i = 0; i < count; i++) {
            std::cout << human_to_string(tourists_ptr, entry->tourists[i]);
            std::cout << "\n\t\t\t\t\t\t\t\t\t\t";
        }
        std::cout << std::endl;
    }
}

template<>
void min_ui_main<employe_t>::table_print(db_base<employe_t>* table) {
    std::cout << "id" << '\t'
              << "Surname" << '\t'
              << "Name" << '\t'
              << "Patronymic" << '\t'
              << "Phone number" << '\t'
              << "Role" << std::endl;
    db_id_t max = table->db_size();
    for (db_id_t i = 0; i < max; i++) {
        auto entry = table->record_read(i);
        if (!(entry->metadata.allow && entry->metadata.show)) continue;
        if (entry->metadata.corrupt) std::cout << "!";
        std::cout << entry->metadata.id << '\t'
                  << entry->surname << '\t'
                  << entry->name << '\t'
                  << entry->patronymic << '\t'
                  << phone_to_str(entry->phone_number) << '\t'
                  << role_pretty(entry->role) << std::endl;
    }
}

#define restore_old_value (buf == "-" && old_data != nullptr)

template<>
tourist_t min_ui_main<tourist_t>::create_record(tourist_t* old_data) {
    _clean_input_buffer();
    tourist_t tmp;
    std::string buf;
    std::cout << "Surname: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->surname << std::endl;
        tmp.surname = old_data->surname;
    }
    else tmp.surname = buf;
    
    std::cout << "Name: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->name << std::endl;
        tmp.name = old_data->name;
    }
    else tmp.name = buf;
    
    std::cout << "Patronymic: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->patronymic << std::endl;
        tmp.patronymic = old_data->patronymic;
    }
    else tmp.patronymic = buf;
    
    std::cout << "Passport series: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->passport_series << std::endl;
        tmp.passport_series = old_data->passport_series;
    }
    else tmp.passport_series = std::stoi(buf);
    
    std::cout << "Passport number: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->passport_number << std::endl;
        tmp.passport_number = old_data->passport_number;
    }
    else tmp.passport_number = std::stoi(buf);
    
    std::cout << "Phone number: ";
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
    _clean_input_buffer();
    std::string buf;
    tour_t tmp;

    std::cout << "Town from: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->town_from << std::endl;
        tmp.town_from = old_data->town_from;
    }
    else tmp.town_from = buf;
    
    std::cout << "Town to: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->town_to << std::endl;
        tmp.town_to = old_data->town_to;
    }
    else tmp.town_to = buf;
    
    std::cout << "Start date: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->date_start << std::endl;
        tmp.date_start = old_data->date_start;
    }
    else tmp.date_start.set(buf);
    
    std::cout << "End date: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->date_end << std::endl;
        tmp.date_end = old_data->date_end;
    }
    else tmp.date_end.set(buf);
    
    std::cout << "Manager: ";
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
    //_clean_input_buffer();
    employe_t tmp;
    std::string buf;
    std::cout << "Surname: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->surname << std::endl;
        tmp.surname = old_data->surname;
    }
    else tmp.surname = buf;
    
    std::cout << "Name: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->name << std::endl;
        tmp.name = old_data->name;
    }
    else tmp.name = buf;
    
    std::cout << "Patronymic: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->patronymic << std::endl;
        tmp.patronymic = old_data->patronymic;
    }
    else tmp.patronymic = buf;
    
    std::cout << "Phone number: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << old_data->phone_number << std::endl;
        tmp.phone_number = old_data->phone_number;
    }
    else tmp.phone_number = str_to_phone(buf);

    std::cout << "Role: ";
    std::getline(std::cin, buf);
    if (restore_old_value) {
        std::cout << "Field stays at " << role_pretty(old_data->role) << std::endl;
        tmp.role = old_data->role;
    }
    else {
        tmp.role = (roles_enum)std::stoi(buf);
    }

    std::cout << "Password: ";
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