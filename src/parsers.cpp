// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <string>
#include <iostream>

#include "parsers.h"
#include "io.h"
#include "base.h"

template <>
bool parsers<tourist_t>::parse(const std::string &str, tourist_t* t) {
   std::string buf;
	size_t left = 0, right = str.find(','), field = 0;
	bool is_good = true;
	try {
		while (field < 7) {
			buf = str.substr(left, right - left).substr(buf.find_first_not_of(' '));
			if (buf.empty()) is_good = false;
			switch (field) {
         case 0:
				t->metadata.id = std::stoull(buf);
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
				if (t->passport_series < 1000 || t->passport_series > 9999) is_good = false;
				break;
			case 5:
				t->passport_number = std::stoi(buf);
				if (t->passport_number < 100000 || t->passport_number > 999999) is_good = false;
				break;
			case 6:
				t->phone_number = std::stoull(buf);
				break;
			default:
				break;
			}
			field++;
			left = right + 1;
			right = str.find(',', right + 1);
			if (right == -1) right = str.length();
		}
	}
	catch (std::exception &e) { return false; }
	return is_good;
}

template <>
bool parsers<tour_t>::parse(const std::string &str, tour_t* t) {
   std::string buf;
   size_t left = 0, right = str.find(','), field = 0;
   bool is_good = true;
   try {
   while (field < 7) {
         buf = str.substr(left, right - left).substr(buf.find_first_not_of(' '));
         if (buf.empty()) is_good = false;
         switch (field) {
         case 0:
		   	t->metadata.id = std::stoull(buf);
	   		break;
         case 1:
            t->town_from = buf;
            break;
         case 2:
            t->town_to = buf;
            break;
         case 3: {
            date d(buf);
            if (!(d.validate())) is_good = false;
            break;
         }
         case 4: {
            date d(buf);
            if (!(d.validate() && d > t->date_start)) is_good = false;
            break;
         }
         case 5:
            t->manager = std::stoll(buf);
            break;
         case 6: {
            size_t count = 0;
            t->tourists = parse_tourists_count(buf, &count);
            t->tourists_count = count;
            break;
         }
         default:
            break;
         }
         field++;
         left = right + 1;
         right = str.find(',', right + 1);
         if (right == -1) right = str.length();
      }
   }
   catch (std::exception &e) { return false; }
   return is_good;
}

template <>
bool parsers<employe_t>::parse(const std::string &str, employe_t* t) {
   std::string buf;
	size_t left = 0, right = str.find(','), field = 0;
	bool is_good = true;
	try {
		while (field < 7) {
			buf = str.substr(left, right - left).substr(buf.find_first_not_of(' '));
			if (buf.empty()) is_good = false;
			switch (field) {
         case 0:
				t->metadata.id = std::stoull(buf);
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
				t->phone_number = std::stoull(buf);
				break;
			default:
				break;
			}
			field++;
			left = right + 1;
			right = str.find(',', right + 1);
			if (right == -1) right = str.length();
		}
	}
	catch (std::exception &e) { return false; }
	return is_good;
}

const bool operator>(const date& d1, const date& d2) {
    if (d1.year > d2.year) return false;
    if (d1.month > d2.month) return false;
    if (d1.day > d2.day) return false;
    return true;
}
const bool operator<(const date& d1, const date& d2) {
    if (d1.year < d2.year) return false;
    if (d1.month < d2.month) return false;
    if (d1.day < d2.day) return false;
    return true;
}

std::ostream& operator<<(std::ostream& out, const date& date) {
    out << date.day << '.' << date.month << '.' << date.year;
    return out;
}

date::date(const std::string& str) {
    set(str);
}

date::date() {
   day = 1; month = 1; year = 1980;
}

date::date(unsigned short new_day, unsigned short new_month, int new_year) {
    set(new_day, new_month, new_year);
}

void date::set(std::string str) {
   // Switch to dots before parsing
   const auto size = str.length();
   for (size_t i = 0; i < size; i++)
      if (str[i] == ',' || str[i] == ' ') str[i] = '.';
   try {

      const auto month_pos = str.find('.');
      const auto year_pos = str.find('.', month_pos + 1);

      day = std::stoi(str.substr(0, month_pos));
      month = std::stoi(str.substr(month_pos + 1, year_pos));
      year = std::stoi(str.substr(year_pos + 1, str.npos));
   }
   catch (const std::exception &e) {
      day = 1; month = 1; year = 1980;
   }
}

void date::set(unsigned short new_day, unsigned short new_month, int new_year) {
    day = new_day; month = new_month; year = new_year;
}

bool date::validate() {
    if (day > 31 || month > 12) {
       return false;
    }

    if (day == 31 &&
       (month == 4 || month == 6 || month == 9 || month == 11)) {
       return false;
    }

    if (month == 2 && day == 29 && // Если 29 февраля
       !((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) { // и год не високосный
       return false;
    }
    return true;
}
