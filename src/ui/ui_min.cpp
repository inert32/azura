#include <stdexcept>
#include "ui_min.h"

#ifndef __linux__
#include <Windows.h>
#endif

min_tui::min_tui() {
#ifndef __linux__
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
}

min_tui::~min_tui() {
    return;
}

bool min_ui::ask_pass() {
    std::string passwd;
    std::cout >> "Enter your password: "
    std::getline(std::cin,, passwd);
    
}

bool min_tui::main_cycle(tourist_ctl* t) {
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

void min_tui::pause() {
	system("pause");
}

void min_tui::msg(const std::string& msg) {
	std::cout << msg << std::endl;
}

void min_tui::draw_table(tourist_ctl* t) {
    auto max = t->db_size();
    std::cout << "Id\tSurname\tName\tPatronymic\tSeries\tNumber\tPhone\n";

	tourist_t* record;
    for (int i = 0; i < max; i++) {
        record = t->record_get(i);
        std::cout << record->id << '\t' << record->surname << '\t' << record->name
            << '\t' << record->patronymic << '\t' << record->passport_series
            << '\t' << record->passport_number << '\t' << record->phone_number << std::endl;
    }
}

void min_tui::draw_table(tour_ctl* t) {}
void min_tui::draw_table(employe_ctl* t) {}

void min_tui::input(tourist_ctl* t) {
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

void min_tui::edit(tourist_ctl* t) {
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
void min_tui::remove(tourist_ctl* t) {
    db_id_t i = 0;
    std::cout << "Which? >";
    std::cin >> i;
    t->record_del(i);
}

bool min_tui::main_cycle(tour_ctl* t) {
    return false;
}
bool min_tui::main_cycle(employe_ctl* t) {
    return false;
}

void min_tui::input(tour_ctl* t) {}
void min_tui::input(employe_ctl* t) {}
