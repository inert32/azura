#ifndef __BASE_H__
#define __BASE_H__

#include <string>
#include <vector>
#include "locale.h"

typedef unsigned long long int db_id_t;

struct date_t {
    unsigned char day = 0;
    unsigned char month = 0;
    unsigned int year = 0;
};

struct _metad {
    db_id_t id = 0;
    bool _corrupt = false;
};

struct tourist_t {
    _metad metadata;
    std::string surname = "";
    std::string name = "";
    std::string patronymic = "";
    unsigned short int passport_series = 0;
    unsigned int passport_number = 0;
    unsigned long long int phone_number = 0;
};

struct tour_t {
    _metad metadata;
    std::string town_from = "";
    std::string town_to = "";
    date_t date_start = { 0, 0, 0 };
    date_t date_end = { 0, 0, 0 };
    db_id_t manager = 0;
    unsigned int tourists_count = 0;
    db_id_t* tourists = nullptr;
};

struct employe_t {
    _metad metadata;
    std::string surname = "";
    std::string name = "";
    std::string patronymic = "";
    unsigned int phone_number = 0;
};

#endif /* __BASE_H__ */
