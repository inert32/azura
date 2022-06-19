// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "parsers.h"

template<>
bool parsers<tourist_t>::validate(const unparsed_t* from, tourist_t* to, bool check_id) {
    db_id_t dummy_id = -1; // records id pool if we can`t read true id
    bool is_good = true;
    int i = 0;
    if (check_id == false) i++;
    for (; i < 7; i++) {
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
                if (to->passport_number < 100000 || to->passport_number > 999999) is_good = false;
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
unparsed_t parsers<tourist_t>::record_to_raw(tourist_t* from) {
    unparsed_t raw;
    raw.fields[0] = std::to_string(from->metadata.id);
    raw.fields[1] = from->surname;
    raw.fields[2] = from->name;
    raw.fields[3] = from->patronymic;
    raw.fields[4] = std::to_string(from->passport_series);
    raw.fields[5] = std::to_string(from->passport_number);
    raw.fields[6] = std::to_string(from->phone_number);
    return raw;
}

template<>
bool parsers<tour_t>::validate(const unparsed_t* from, tour_t* to, bool check_id) {
    db_id_t dummy_id = -1; // records id pool if we can`t read true id
    bool is_good = true;
    int i = 0;
    if (check_id == false) i++;
    for (; i < 7; i++) {
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
unparsed_t parsers<tour_t>::record_to_raw(tour_t* from) {
    unparsed_t raw;
    raw.fields[0] = std::to_string(from->metadata.id);
    raw.fields[1] = from->town_from;
    raw.fields[2] = from->town_to;
    raw.fields[3] = from->date_start.to_string();
    raw.fields[4] = from->date_end.to_string();
    raw.fields[5] = std::to_string(from->manager);
    const auto count = from->tourists.size();
	for (size_t i = 0; i < count; i++) {
		raw.fields[6] += std::to_string(from->tourists[i]);
		if (i + 1 < count) raw.fields[6] += ';';
	}
    return raw;
}

template<>
bool parsers<employe_t>::validate(const unparsed_t* from, employe_t* to, bool check_id) {
    db_id_t dummy_id = -1; // records id pool if we can`t read true id
    bool is_good = true;
    int i = 0;
    if (check_id == false) i++;
    for (; i < 7; i++) {
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
            try {
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
            }
            catch (std::exception& e) {
                to->role = roles_enum::guide;
            }
            break;
        case 6:
            to->passwd = from->fields[i];
            break;
        }
    }
    return is_good;
}

template<>
unparsed_t parsers<employe_t>::record_to_raw(employe_t* from) {
    unparsed_t raw;
    raw.fields[0] = std::to_string(from->metadata.id);
    raw.fields[1] = from->surname;
    raw.fields[2] = from->name;
    raw.fields[3] = from->patronymic;
    raw.fields[4] = std::to_string(from->phone_number);
    raw.fields[5] = std::to_string((int)from->role);
    raw.fields[6] = from->passwd;
    return raw;
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
