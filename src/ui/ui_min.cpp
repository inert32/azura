// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef __linux__
#include <Windows.h>
#endif

#include "ui_min.h"

min_ui::min_ui() {
#ifndef __linux__
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
}

min_ui::~min_ui() {
    return;
}

bool min_ui::login() {
    std::string passwd;
	std::cout << "Enter your password: ";
    std::getline(std::cin, passwd);
	return true;
}

bool min_ui::main_cycle(tourist_ctl* t) {
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
      return false;
      break;
    }
    return true;
}

void min_ui::msg(std::string_view msg) {
    std::cout << msg << std::endl;
}

void min_ui::msg(std::string_view head, std::string_view msg) {
    std::cout << head << std::endl << msg << std::endl;
}

void min_ui::draw_table(tourist_ctl* t) {
    auto max = t->db_size();
    std::cout << "Id\tSurname\tName\tPatronymic\tSeries\tNumber\tPhone\n";

    tourist_t* record;
    for (int i = 0; i < max; i++) {
      record = t->record_get(i);
	  if (record->_corrupt) std::cout << '!';
      std::cout << record->id << '\t' << record->surname << '\t' << record->name
        << '\t' << record->patronymic << '\t' << record->passport_series
        << '\t' << record->passport_number << '\t' << record->phone_number << std::endl;
    }
}

void min_ui::draw_table(tour_ctl* t) {}
void min_ui::draw_table(employe_ctl* t) {}

void min_ui::input(tourist_ctl* t) {
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
    t->record_make(&test_input);
}

void min_ui::edit(tourist_ctl* t) {
    db_id_t i = 0, max = t->db_size();
    std::cout << "Which? >";
    std::cin >> i;
    std::cin.get();
    if (i < max) {
      tourist_t record;
      record.id = i;
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
      t->record_edit(i, &record);
    }
}
void min_ui::remove(tourist_ctl* t) {
    db_id_t i = 0;
    std::cout << "Which? >";
    std::cin >> i;
    t->record_del(i);
}

bool min_ui::main_cycle(tour_ctl* t) {
    return false;
}
bool min_ui::main_cycle(employe_ctl* t) {
    return false;
}

void min_ui::input(tour_ctl* t) {}
void min_ui::input(employe_ctl* t) {}
