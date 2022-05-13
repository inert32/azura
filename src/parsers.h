#ifndef __PARSERS_H__
#define __PARSERS_H__
#include "base.h"

template<class T>
class parsers {
public:
    bool parse(const std::string& str, T* t);
    void parse_tourists_count(const std::string &str, std::vector<db_id_t>* list);
};

template<class T>
class prettify_records {
public:
    void prettyify(T* record);
    std::string capitalize(const std::string& str);
};

std::string phone_to_str(const unsigned long long int number); 
unsigned long long int str_to_phone(const std::string& buf);

template<class T>
std::string prettify_records<T>::capitalize(const std::string& str) {
    std::string new_string;
    const auto len = str.length();
    bool word_end = true;

    for (size_t i = 0; i < len; i++) {
        if (std::isalpha(str[i]) == 0) {
            word_end = true;
            new_string += str[i];
            continue;
        }
        if (word_end == true) {
            word_end = false;
            new_string += std::toupper(str[i]);
        }
        else new_string += std::tolower(str[i]);
    }
    return new_string;
}

template<class T>
void parsers<T>::parse_tourists_count(const std::string &str, std::vector<db_id_t>* list) {
    size_t left = 0, right = str.find(',');
    while (true) {
        if (left > right) break;
        std::string buf = str.substr(left, right - left);
        if (!buf.empty()) list->push_back(std::stoull(buf));
        else break; // Stop if there is no more values

        left = right + 1;
        right = str.find(',', right + 1);
        if (right == str.npos) right = str.length();
    }
}

#endif /* __PARSERS_H__ */
