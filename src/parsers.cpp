// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "parsers.h"

template<>
bool parsers<tourist_t>::parse(const std::string &str, tourist_t* t) {
    std::string buf;
    size_t left = 0, right = str.find(','), field = 0;
    bool is_good = true;
    try {
        while (field < 7) {
            buf = str.substr(left, right - left);
            buf = buf.substr(buf.find_first_not_of(' '));
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
                break;
            case 5:
                t->passport_number = std::stoi(buf);
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

template<>
bool parsers<tour_t>::parse(const std::string &str, tour_t* t) {
    std::string buf;
    size_t left = 0, right = str.find(','), field = 0;
    bool is_good = true;
    try {
        while (field < 7) {
            buf = str.substr(left, right - left);
            buf = buf.substr(buf.find_first_not_of(' '));
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
                t->date_start.set(buf);
                if (!(t->date_start.validate())) is_good = false;
                break;
            }
            case 4: {
                t->date_end.set(buf);
                if (!(t->date_end.validate())) is_good = false;
                break;
            }
            case 5:
                t->manager = std::stoll(buf);
                break;
            case 6: {
                size_t count = 0;
                parse_tourists_count(buf, &t->tourists);
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

template<>
bool parsers<employe_t>::parse(const std::string &str, employe_t* t) {
    std::string buf;
    size_t left = 0, right = str.find(','), field = 0;
    bool is_good = true;
    try {
        while (field < 7) {
            buf = str.substr(left, right - left);
            buf = buf.substr(buf.find_first_not_of(' '));
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
            case 5:
                t->role = (roles_enum)std::stoi(buf);
                break;
            case 6:
                t->passwd = buf;
                break;
            default: break;
            }
            field++;
            left = right + 1;
            right = str.find(',', right + 1);
            if (right == str.npos) right = str.length();
        }
    }
    catch (std::exception &e) { return false; }
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
    std::string buf;
    int part1 = number / 10000000;
    int part2 = number % 10000000;
    int part3 = part2 % 10000;
    part2 = part2 / 10000;
    buf += std::to_string(part1 / 1000) + " (" + std::to_string(part1 % 1000) + ") ";
    buf += std::to_string(part2) + " " + std::to_string(part3 / 100) + '-' + std::to_string(part3 % 100);
    return buf;
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
