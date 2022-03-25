#ifndef __BASE_H__
#define __BASE_H__

#include <string>
#include <vector>

typedef unsigned long long int db_id_t;

struct date_t {
    unsigned char day;
    unsigned char month;
    unsigned int year;
};

struct tourist_t {
     db_id_t id = 0;
     std::string surname = "";
     std::string name = "";
     std::string patronymic = "";
     unsigned short int passport_series = 0;
     unsigned int passport_number = 0;
     unsigned long long int phone_number = 0;
};

struct tour_t {
     db_id_t id;
     std::string town_from;
     std::string town_to;
     date_t date_start;
     date_t date_end;
     db_id_t manager;
     unsigned int tourists_count;
     db_id_t* tourists;
};

struct employe_t {
     db_id_t id;
     std::string surname;
     std::string name;
     std::string patronymic;
     unsigned int phone_number;
};

#endif
