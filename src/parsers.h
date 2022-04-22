#ifndef __PARSERS_H__
#define __PARSERS_H__
#include "base.h"

class date {
public:
    date(const std::string& str);
    bool later_than(const date_t* d);
    void set(const std::string& str);

    bool validate();
    date_t get_date();
private:
    date_t dt;
};

bool parse_tourist_t(const std::string &str, tourist_t* t);
bool parse_tour_t(const std::string &str, tour_t* t);
bool parse_employe_t(const std::string &str, employe_t* t);

#endif /* __PARSERS_H__ */
