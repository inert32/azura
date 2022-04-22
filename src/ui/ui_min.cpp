// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef __linux__
#include <Windows.h>
#endif

#include "ui_min.h"

min_ui::min_ui() {
    #ifndef __linux__
    // Enabling Unicode in Windows console
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    #endif
    std::cout << "Azura v" << AZ_VER_MAJOR << '.' << AZ_VER_MINOR << '.' << AZ_VER_PATCH << std::endl;
}

min_ui::~min_ui() {
    return;
}

bool min_ui::login() {
	return true;
}

void min_ui::get_tables(db_base<tourist_t>* a, db_base<tour_t>* b, db_base<employe_t>* c) {
    tourists = a; tours = b; employes = c;
    current_table = ui_tables_list::tourist_t;
}

void min_ui::msg(std::string_view msg) {
    std::cout << msg << std::endl;
}

void min_ui::msg(std::string_view head, std::string_view msg) {
    std::cout << head << std::endl << msg << std::endl;
}

void min_ui::main() {
    bool run = true;
    while (run) {
        switch (current_table) {
        case ui_tables_list::tourist_t:
            run = print_menu(tourists);
            break;
        case ui_tables_list::tour_t:
            run = print_menu(tours);
            break;
        case ui_tables_list::employe_t:
            run = print_menu(employes);
            break;
        default:
            break;
        }
    }
}

bool min_ui::print_menu(db_base<tourist_t>* t) {
    draw_table(t);
    msg("Enter 1 to create, 2 to edit, 3 to delete, 0 to exit");
	int c;
    std::cout << ">";
    std::cin >> c;
    std::cin.get();
	switch (c) {
    case 1:
	    input(t);
	   	break;
    case 2:
	    edit(t);
	   	break;
    case 3:
	    remove(t);
	   	break;
    case 0:
	    [[fallthrough]];
	default:
    	tourists->db_sync();
	    return false;
    }
    return true;
}

bool min_ui::print_menu(db_base<tour_t>* t) {
    draw_table(t);
    msg("Enter 1 to create, 2 to edit, 3 to delete, 0 to exit");
	int c;
    std::cout << ">";
    std::cin >> c;
    std::cin.get();
	switch (c) {
    case 1:
	    input(t);
	   	break;
    case 2:
	    edit(t);
	   	break;
    case 3:
	    remove(t);
	   	break;
    case 0:
	    [[fallthrough]];
	default:
    	tours->db_sync();
	    return false;
    }
    return true;
}

bool min_ui::print_menu(db_base<employe_t>* t) {
    draw_table(t);
    msg("Enter 1 to create, 2 to edit, 3 to delete, 0 to exit");
	int c;
    std::cout << ">";
    std::cin >> c;
    std::cin.get();
	switch (c) {
    case 1:
	    input(t);
	   	break;
    case 2:
	    edit(t);
	   	break;
    case 3:
	    remove(t);
	   	break;
    case 0:
	    [[fallthrough]];
	default:
    	employes->db_sync();
	    return false;
    }
    return true;
}

void min_ui::draw_table(db_base<tourist_t>* t) {
    auto max = t->db_size();
    std::cout << "Id\tSurname\tName\tPatronymic\tSeries\tNumber\tPhone\n";

    tourist_t* record;
    for (int i = 0; i < max; i++) {
      record = t->record_get(i);
	  if (record->metadata._corrupt) std::cout << '!';
      std::cout << record->metadata.id << '\t' << record->surname << '\t' << record->name
        << '\t' << record->patronymic << '\t' << record->passport_series
        << '\t' << record->passport_number << '\t' << record->phone_number << std::endl;
    }
}

void min_ui::draw_table(db_base<tour_t>* t) {}

void min_ui::draw_table(db_base<employe_t>* t) {}

void min_ui::input(db_base<tourist_t>* t) {
    tourist_t test_input;
    std::cout << "F> ";
    std::getline(std::cin, test_input.surname);
    std::cout << "I> ";
    std::getline(std::cin, test_input.name);
    std::cout << "O> ";
    std::getline(std::cin, test_input.patronymic);
    std::cout << "S> ";
    std::cin >> test_input.passport_series;
    std::cout << "N> ";
    std::cin >> test_input.passport_number;
    std::cout << "P> ";
    std::cin >> test_input.phone_number;
    t->record_add(&test_input);
}

void min_ui::input(db_base<tour_t>* t) {}

void min_ui::input(db_base<employe_t>* t) {}

void min_ui::edit(db_base<tourist_t>* t) {
    db_id_t i = 0, max = t->db_size();
    std::cout << "Which? >";
    std::cin >> i;
    std::cin.get();
    if (i < max) {
      tourist_t record;
      record.metadata.id = i;
      std::cout << "F> ";
      std::getline(std::cin, record.surname);
      std::cout << "I> ";
      std::getline(std::cin, record.name);
      std::cout << "O> ";
      std::getline(std::cin, record.patronymic);
      std::cout << "S> ";
       std::cin >> record.passport_series;
      std::cout << "N> ";
       std::cin >> record.passport_number;
      std::cout << "P> ";
       std::cin >> record.phone_number;
      t->record_edit(&record, i);
    }
}

void min_ui::edit(db_base<tour_t>* t) {}

void min_ui::edit(db_base<employe_t>* t) {}

void min_ui::remove(db_base<tourist_t>* t) {
    db_id_t i = 0;
    std::cout << "Which? >";
    std::cin >> i;
    t->record_del(i);
}

void min_ui::remove(db_base<tour_t>* t) {}

void min_ui::remove(db_base<employe_t>* t) {}