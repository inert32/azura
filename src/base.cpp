// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "base.h"

std::string purify_buf(const std::string& buf) {
    std::string out = buf.substr(buf.find_first_not_of(' '));
    return out.substr(0, out.find_first_of(' '));
}

const bool operator>(const date& d1, const date& d2) {
    constexpr auto sec_in_year = 31536000;
    constexpr auto leap_seconds = 86400;

    unsigned long long int unixtime_d1 = sec_in_year;
    if (d1.is_leap()) unixtime_d1 += leap_seconds;

    unsigned long long int unixtime_d2 = sec_in_year;
    if (d2.is_leap()) unixtime_d2 += leap_seconds;

    return unixtime_d1 > unixtime_d2;
}
const bool operator<(const date& d1, const date& d2) {
    constexpr auto sec_in_year = 31536000;
    constexpr auto leap_seconds = 86400;

    unsigned long long int unixtime_d1 = sec_in_year;
    if (d1.is_leap()) unixtime_d1 += leap_seconds;

    unsigned long long int unixtime_d2 = sec_in_year;
    if (d2.is_leap()) unixtime_d2 += leap_seconds;

    return unixtime_d1 < unixtime_d2;
}

std::ostream& operator<<(std::ostream& out, const date& date) {
    out << std::to_string(date.day) + '.' + std::to_string(date.month) + '.' + std::to_string(date.year);
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

        if (year < 2000) year += 2000;
    }
    catch (const std::exception &e) {
        day = 1; month = 1; year = 1980;
    }
}

void date::set(unsigned short new_day, unsigned short new_month, int new_year) {
    day = new_day; month = new_month; year = new_year;
    if (year < 2000) year += 2000;
}

bool date::validate() {
    if (day == 0 || month == 0) return false;

    if (day > 31 || month > 12) return false;

    if (day == 31 &&
       (month == 4 || month == 6 || month == 9 || month == 11)) return false;

    if (month == 2 && day == 29 && // Если 29 февраля
       !((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) // и год не високосный
       return false;
       
    return true;
}

bool date::is_leap() const {
    return (month == 2 && day == 29 && // Если 29 февраля
           ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)); // и год не високосный
}

std::string date::to_string() {
    return std::to_string(day) + '.' + std::to_string(month) + '.' + std::to_string(year);
}

std::string role_pretty(const roles_enum role) {
    switch (role) {
        case roles_enum::guide:   return "Guide";
        case roles_enum::manager: return "Manager";
        case roles_enum::chief:   return "Chief";
        default:                  return "Guide";
    }
}
