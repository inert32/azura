#ifndef __UI_MIN_H__
#define __UI_MIN_H__

#include "ui.h"

#ifdef AZ_USE_MIN_UI

#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif

class min_ui : public ui_base {
public:
    min_ui();

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
class min_ui_main {
public:
    void set_tables(db_base<tourist_t>* tourists, db_base<tour_t>* tours, db_base<employe_t>* employes);
    tables_list main(db_base<T>* table, const tables_list current);
    T create_record(T* old_data = nullptr);

private:
    void record_create(db_base<T>* table);
    void record_update(db_base<T>* table);
    void record_delete(db_base<T>* table);
    void table_print(db_base<T>* table);

    ui_actions print_menu();
    tables_list switch_table();

    void _clean_input_buffer();
    db_base<tourist_t>* tourists_ptr;
    db_base<tour_t>* tours_ptr;
    db_base<employe_t>* employes_ptr;
};

template<class T>
void min_ui_main<T>::set_tables(db_base<tourist_t>* tourists, db_base<tour_t>* tours, db_base<employe_t>* employes) {
    tourists_ptr = tourists;
    tours_ptr = tours;
    employes_ptr = employes;
}

template<class T>
tables_list min_ui_main<T>::switch_table() {
    std::cout << "Tables: " << std::endl
              << "1 - Tourists" << std::endl
              << "2 - Tours" << std::endl
              << "3 - Employes" << std::endl
              << "Enter table number: ";
    while (true) {
        char c = 0;
        std::cin >> c;
        switch (c) {
            case '1': return tables_list::tourists;
            case '2': return tables_list::tours;
            case '3': return tables_list::employes;
            default:  break;
        }
    }
}

template<class T>
void min_ui_main<T>::_clean_input_buffer() {
    std::cin.get();
}

template<class T>
tables_list min_ui_main<T>::main(db_base<T>* table, const tables_list current) {
    // Check that table here and table from set_tables() same
    table_print(table);
    switch (print_menu()) {
    case ui_actions::record_create:
        record_create(table);
        break;
    case ui_actions::record_update:
        record_update(table);
        break;
    case ui_actions::record_delete:
        record_delete(table);
        break;
    case ui_actions::switch_table:
        return switch_table();
    case ui_actions::quit:
        return tables_list::_quit;
    }
    return current;
}

template<class T>
ui_actions min_ui_main<T>::print_menu() {
    std::cout << "1 - New record, 2 - Edit record, 3 - Delete record" << std::endl;
    std::cout << "9 - Switch table, 0 - Quit : ";
    while (true) {
        char c = 0;
        std::cin >> c;
        switch (c) {
            case '1': return ui_actions::record_create;
            case '2': return ui_actions::record_update;
            case '3': return ui_actions::record_delete;
            case '9': return ui_actions::switch_table;
            case '0': return ui_actions::quit;
            default: break;
        }
    }
}

template<class T>
void min_ui_main<T>::record_create(db_base<T>* table) {
    auto rec = create_record();
    table->record_create(&rec);
}

template<class T>
void min_ui_main<T>::record_update(db_base<T>* table) {
    std::cout << "Enter id: ";
    db_id_t id = 0;
    std::cin >> id;
    auto old = table->record_read(id);
    if (old != nullptr) {
        std::cout << "Type '-' to enter old value" << std::endl;
        auto rec = create_record(old);
        table->record_update(&rec, id);
    }
    else std::cout << "No such record." << std::endl;
}

template<class T>
void min_ui_main<T>::record_delete(db_base<T>* table) {
    std::cout << "Enter id: ";
    db_id_t id = 0;
    std::cin >> id;
    if (table->record_exists(id)) {
        std::cout << "Sure? (y/n) ";
        char c = 0;
        std::cin >> c;
        if (tolower(c) == 'y') table->record_delete(id);
        else std::cout << "Removal canceled" << std::endl;
    }
    else std::cout << "No such record." << std::endl;
}

#endif /* AZ_USE_MIN_UI */

#endif /* __UI_MIN_H__ */