#ifndef __PARSERS_H__
#define __PARSERS_H__
#include "base.h"

#ifdef _WIN32
	#define is_letter(c) isalpha((unsigned char)(c))
	#define is_digit(c)  isdigit((unsigned char)(c))
	#define to_upper(c)  toupper((unsigned char)(c))
	#define to_lower(c)  tolower((unsigned char)(c))
#else
	#define is_letter(c) std::isalpha((unsigned char)(c))
	#define is_digit(c)  std::isdigit((unsigned char)(c))
	#define to_upper(c)  std::toupper((unsigned char)(c))
	#define to_lower(c)  std::tolower((unsigned char)(c))
#endif

std::string phone_to_str(const unsigned long long int number); 
unsigned long long int str_to_phone(const std::string& buf);

template<class T>
class parsers {
public:
    unparsed_t parse(const std::string& str);
    unparsed_t record_to_raw(T* from);

    bool validate(const unparsed_t* from, T* to, bool check_id = true);
    void parse_tourists_count(const std::string &str, std::vector<db_id_t>* list);
};

template<class T>
unparsed_t parsers<T>::parse(const std::string& str) {
    unparsed_t raw;
    std::string buf;
    size_t left = 0, right = str.find(','), field = 0;

    for (int i = 0; i < 7; i++) {
        buf = str.substr(left, right - left);
        raw.fields[i] = purify_buf(buf);

        left = right + 1;
        right = str.find(',', right + 1);
        if (right == -1) right = str.length();
    }
    return raw;
}

template<class T>
class prettify_records {
public:
    void prettyify(T* record);
    std::string capitalize(const std::string& str);
};

template<class T>
std::string prettify_records<T>::capitalize(const std::string& str) {
    std::string new_string;
    const auto len = str.length();
    bool word_end = true;

    for (size_t i = 0; i < len; i++) {
        if (is_letter(str[i]) == 0) {
            word_end = true;
            new_string += str[i];
            continue;
        }
        if (word_end == true) {
            word_end = false;
            new_string += to_upper(str[i]);
        }
        else new_string += to_lower(str[i]);
    }
    return new_string;
}

template<class T>
void parsers<T>::parse_tourists_count(const std::string &str, std::vector<db_id_t>* list) {
    size_t left = 0, right = str.find(';');
    const auto len = str.length();
    while (true) {
        std::string buf = str.substr(left, right - left);
        if (!buf.empty()) list->push_back(std::stoull(buf));
        left = right + 1;
        if (left > len) break;
        right = str.find(';', left);
        if (right == str.npos) right = len;
    }
}

#endif /* __PARSERS_H__ */
