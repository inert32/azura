// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "parsers.h"

template<>
bool parsers<tourist_t>::validate(const unparsed_t* from, tourist_t* to) {
    db_id_t dummy_id = -1; // records id pool if we can`t read true id
    bool is_good = true;
    for (int i = 0; i < 7; i++) {
        if (from->fields[i].empty()) {
            is_good = false;
            continue;
        }
        switch (i) {
        case 0:
            try {
                to->metadata.id = std::stoull(from->fields[i]);
            }
            catch (std::exception& e) {
                is_good = false;
                to->metadata.id = dummy_id;
                dummy_id--;
            }
            break;
        case 1:
            to->surname = from->fields[i]; break;
        case 2:
            to->name = from->fields[i]; break;
        case 3:
            to->patronymic = from->fields[i]; break;
        case 4:
            try {
                to->passport_series = std::stoi(from->fields[i]);
                if (to->passport_series < 1000 || to->passport_series > 9999) is_good = false;
            }
            catch (std::exception& e) {
                is_good = false;
            }
            break;
        case 5:
            try {
                to->passport_number = std::stoi(from->fields[i]);
                if (to->passport_series < 100000 || to->passport_series > 999999) is_good = false;
            }
            catch (std::exception& e) {
                is_good = false;
            }
            break;
        case 6:
            try {
                to->phone_number = std::stoull(from->fields[i]);
                if (to->phone_number < 10000000000) is_good = false;
            }
            catch (std::exception& e) {
                is_good = false;
            }
            break;
        }
    }
    return is_good;
}

template<>
bool parsers<tour_t>::validate(const unparsed_t* from, tour_t* to) {
    db_id_t dummy_id = -1; // records id pool if we can`t read true id
    bool is_good = true;
    for (int i = 0; i < 7; i++) {
        if (from->fields[i].empty()) {
            is_good = false;
            continue;
        }
        switch (i) {
        case 0:
            try {
                to->metadata.id = std::stoull(from->fields[i]);
            }
            catch (std::exception& e) {
                is_good = false;
                to->metadata.id = dummy_id;
                dummy_id--;
            }
            break;
        case 1:
            to->town_from = from->fields[i]; break;
        case 2:
            to->town_to = from->fields[i]; break;
        case 3:
            to->date_start.set(from->fields[i]);
            if (to->date_start.validate() == false) is_good = false;
            break;
        case 4:
            to->date_end.set(from->fields[i]);
            if (to->date_end.validate() == false || 
            to->date_start > to->date_end) is_good = false;

            break;
        case 5:
            try {
                to->manager = std::stoull(from->fields[i]);
            }
            catch (std::exception& e) {
                is_good = false;
            }
            break;
        case 6:
            parse_tourists_count(from->fields[i], &to->tourists); break;
        }
    }
    return is_good;
}

template<>
bool parsers<employe_t>::validate(const unparsed_t* from, employe_t* to) {
    db_id_t dummy_id = -1; // records id pool if we can`t read true id
    bool is_good = true;
    for (int i = 0; i < 7; i++) {
        if (from->fields[i].empty()) {
            is_good = false;
            continue;
        }
        switch (i) {
        case 0:
            try {
                to->metadata.id = std::stoull(from->fields[i]);
            }
            catch (std::exception& e) {
                is_good = false;
                to->metadata.id = dummy_id;
                dummy_id--;
            }
            break;
        case 1:
            to->surname = from->fields[i]; break;
        case 2:
            to->name = from->fields[i]; break;
        case 3:
            to->patronymic = from->fields[i]; break;
        case 4:
            try {
                to->phone_number = std::stoull(from->fields[i]);
                if (to->phone_number < 10000000000) is_good = false;
            }
            catch (std::exception& e) {
                is_good = false;
            }
            break;
        case 5:
            auto role_raw = std::stoi(from->fields[i]);
            switch (role_raw) {
            case 0:
            default:
                to->role = roles_enum::guide;
                break;
            case 1:
                to->role = roles_enum::manager;
                break;
            case 2:
                to->role = roles_enum::chief;
                break;
            }
        case 6:
            to->passwd = from->fields[i];
            break;
        }
    }
    return is_good;
}

template<>
void prettify_records<tourist_t>::prettyify(tourist_t* record) {
    record->surname = capitalize(record->surname);
    record->name = capitalize(record->name);
    record->patronymic = capitalize(record->patronymic);
}

template<>
void prettify_records<tour_t>::prettyify(tour_t* record) {
    record->town_from = capitalize(record->town_from);
    record->town_to = capitalize(record->town_to);
}

template<>
void prettify_records<employe_t>::prettyify(employe_t* record) {
    record->surname = capitalize(record->surname);
    record->name = capitalize(record->name);
    record->patronymic = capitalize(record->patronymic);
}

std::string phone_to_str(const unsigned long long int number) {
    std::string base = std::to_string(number);
    const auto len = base.length();
    std::string part3 = base.substr(len - 2, 2);
    std::string part2 = base.substr(len - 4, 2);
    std::string part1 = base.substr(len - 7, 3);
    std::string code = base.substr(len - 10, 3);
    std::string country = base.substr(0, len - 10);
    return country + " (" + code + ") " + part1 + '-' + part2 + '-' + part3;
}

unsigned long long int str_to_phone(const std::string& buf) {
    const auto len = buf.length();
    unsigned long long int num = 0;
    for (size_t i = 0; i < len; i++) {
        auto c = buf[i];
        if (is_digit(c)) {
            num *= 10;
            num += c - '0';
        }
    }
    return num;
}
