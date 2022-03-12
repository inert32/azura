#include <string>
#include <iostream>

#include "parsers.h"
#include "io.h"
#include "base.h"

bool parser_tourist_t(const std::string &str, tourist_t* t) {
	std::string buf;
	size_t left = 0, right = str.find(','), sw = 0;
	while (sw < 7) {
		buf = str.substr(left, right - left);
		if (buf.empty()) return false;
		switch (sw) {
		case 0:
			t->id = std::stoi(buf);
            break;
		case 1:
			t->surname = buf; 
            break;
		case 2:
			t->name = buf; 
            break;
		case 3:
			t->patronymic = buf; 
            break;
		case 4:
			t->passport_series = std::stoi(buf); 
            break;
		case 5:
			t->passport_number = std::stoi(buf); 
            break;
		case 6:
			t->phone_number = std::stoll(buf);
            break;
		default:
			break;
		}
		sw++;
		left = right + 1;
		right = str.find(',', right + 1);
		if (right == -1) right = str.length();
	}
	return (!t->phone_number == 0) ? true : false;
}
bool parser_tours_t(const std::string &str, tour_t* t);
bool parser_employe_t(const std::string &str, employe_t* t);
