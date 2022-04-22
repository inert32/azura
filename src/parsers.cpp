// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <string>
#include <iostream>

#include "parsers.h"
#include "io.h"
#include "base.h"

bool parse_tourist_t(const std::string &str, tourist_t* t) {
   std::string buf;
	size_t left = 0, right = str.find(','), sw = 0;
	bool is_good = true;
	try {
		while (sw < 6) {
			buf = str.substr(left, right - left);
			buf = buf.substr(buf.find_first_not_of(' '));
			if (buf.empty()) is_good = false;
			switch (sw) {
			case 0:
				t->surname = buf;
				break;
			case 1:
				t->name = buf;
				break;
			case 2:
				t->patronymic = buf;
				break;
			case 3:
				t->passport_series = std::stoi(buf);
				if (t->passport_series < 1000 || t->passport_series > 9999) is_good = false;
				break;
			case 4:
				t->passport_number = std::stoi(buf);
				if (t->passport_number < 100000 || t->passport_number > 999999) is_good = false;
				break;
			case 5:
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
	}
	catch (std::exception &e) { return false; }
	return is_good;
}

bool parse_tour_t(const std::string &str, tour_t* t) {
    date d("");
    std::string buf;
    size_t left = 0, right = str.find(','), sw = 0;
    while (sw < 6) {
       buf = str.substr(left, right - left);
       if (buf.empty()) return false;
       switch (sw) {
       case 0:
          t->town_from = buf;
          break;
       case 1:
          t->town_to = buf;
          break;
       case 2:
          d.set(buf);
          if (d.validate())
             t->date_start = d.get_date();
          else
             t->date_start = { 1,1,1980 };
          break;
       case 3:
          d.set(buf);
          if (d.validate() && d.later_than(&t->date_start))
             t->date_start = d.get_date();
          else
             t->date_start = { 1,1,1980 };
          break;
       case 4:
          t->manager = std::stoll(buf);
          break;
       case 5:
          t->tourists_count = std::stoll(buf);
          break;
       default:
          break;
       }
       sw++;
       left = right + 1;
       right = str.find(',', right + 1);
       if (right == -1) right = str.length();
    }
    return (!t->manager == 0) ? true : false;
}

bool parse_employe_t(const std::string &str, employe_t* t) {}


date::date(const std::string& str) {
    set(str);
}

void date::set(const std::string& str) {
    size_t month = str.find(','), year = str.find(',', month + 1);

    dt.day = std::stoi(str.substr(0, month));
    dt.month = std::stoi(str.substr(month + 1, year));
    dt.year = std::stoi(str.substr(year + 1, str.npos));
}

bool date::validate() {
    if (dt.day > 31 || dt.month > 12) {
       return false;
    }

    if (dt.day == 31 &&
       (dt.month == 4 || dt.month == 6 || dt.month == 9 || dt.month == 11)) {
       return false;
    }

    if (dt.month == 2 && dt.day == 29 && // Если 29 февраля
       !((dt.year % 4 == 0 && dt.year % 100 != 0) || dt.year % 400 == 0)) { // и год не високосный
       return false;
    }
    return true;
}

date_t date::get_date() {
    return dt;
}

bool date::later_than(const date_t* d) {
    if (dt.year > d->year) return false;
    if (dt.month > d->month) return false;
    if (dt.day > d->day) return false;
    return true;
}
