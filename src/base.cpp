// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "base.h"


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

std::string roles::pretty() {
    switch (user_role) {
        case guide:   return "Guide";
        case manager: return "Manager";
        case chief:   return "Chief";
        default:      return "Guide";
    }
}
void roles::set(const int role) {
    switch (role) {
        case 0:  user_role = guide; break;
        case 1:  user_role = manager; break;
        case 2:  user_role = chief; break;
        default: user_role = guide; break;
    }
}

std::ostream& operator<<(std::ostream& out, const roles& role) {
    switch (role.user_role) {
        case role.guide:   out << 0; break;
        case role.manager: out << 1; break;
        case role.chief:   out << 2; break;
        default:           out << 0; break;
    }
    return out;
}