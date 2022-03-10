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

void min_tui::draw_table(tourist_ctl* t) {
	auto max = t->arr_update();
	std::cout << "Id\tSurname\tName\tPatronymic\tSeries\tNumber\tPhone\n";

	for (int i = 0; i < max; i++) {
		tourist_t record;
		record = *(t->record_get(i));
		std::cout << record.id << '\t' << record.surname << '\t' << record.name
			<< '\t' << record.patronymic << '\t' << record.passport_series
			<< '\t' << record.passport_number << '\t' << record.phone_number << std::endl;
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
	std::getline(std::cin, test_input.passport_series);
	std::cout << "N> ";
	std::getline(std::cin, test_input.passport_number);
	std::cout << "P> ";
	std::getline(std::cin, test_input.phone_number);
	t->record_make(&test_input);
}

void min_tui::choose(tourist_ctl* t) {
	std::cout << "Enter 1 to create, 2 to edit, 3 to delete, 0 to exit" << std::endl;
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
		__fallthrough;
	default:
		throw std::exception("Quit");
		break;
	}
}

void min_tui::edit(tourist_ctl* t) {
	db_id_t i = 0, max = t->arr_size();
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
		std::getline(std::cin, record.passport_series);
		std::cout << "N> ";
		std::getline(std::cin, record.passport_number);
		std::cout << "P> ";
		std::getline(std::cin, record.phone_number);
		t->record_edit(i, &record);
	}
}
void min_tui::remove(tourist_ctl* t) {
	db_id_t i = 0;
	std::cout << "Which? >";
	std::cin >> i;
	t->record_del(i);
}

void min_tui::input(tour_ctl* t) {}
void min_tui::input(employe_ctl* t) {}