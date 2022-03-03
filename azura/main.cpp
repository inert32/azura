// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include "base.h"

#include "tour_ctl.h"
#include "tourist_ctl.h"
#include "employe_ctl.h"

void test_print(tourist_ctl* t) {
	auto max = t->update();
	std::cout << "Id\tSurname\tName\tPatronymic\tSeries\tNumber\tPhone\n";

	for (int i = 0; i < max; i++) {
		tourist_t record;
		record = *(t->get(i));
		std::cout << record.id << '\t' << record.surname << '\t' << record.name
			<< '\t' << record.patronymic << '\t' << record.passport_series
			<< '\t' << record.passport_number << '\t' << record.phone_number << std::endl;
	}
}

void test_insert(tourist_ctl* t) {
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
	t->create(&test_input);
}

int main() {
	std::cout << "v0.01 " << std::endl
		 << "Build date: " << __TIMESTAMP__ << std::endl;
	// Setup files
	tourist_ctl t;
	try {
		t.init(std::filesystem::absolute("tourists.txt"));
	}
	catch (const std::exception &e) {
		std::cout << "Exception recieved: " << e.what() << std::endl;
		return -1;
	}

	test_print(&t);
	test_insert(&t);

	std::cout << "----------------\n";

	test_print(&t);
	
	system("pause");
	return 0;
}