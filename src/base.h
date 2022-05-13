#ifndef __BASE_H__
#define __BASE_H__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "locale.h"

typedef unsigned long long int db_id_t;

class roles {
public:
    std::string pretty();
    void set(const int role);
    friend std::ostream& operator<<(std::ostream& out, const roles& role);
private:
    enum _roles_enum {
        guide,
        manager,
        chief
    } user_role = guide;
};

class date {
public:
    date(const std::string& str);
    date();
    date(unsigned short day, unsigned short month, int year);
    void set(std::string str);
    void set(unsigned short day, unsigned short month, int year);

    bool validate();

    friend const bool operator>(const date& d1, const date& d2);
    friend const bool operator<(const date& d1, const date& d2);
    friend std::ostream& operator<<(std::ostream& out, const date& date);
private:
    unsigned short int day = 1;
    unsigned short int month = 1;
    unsigned int year = 1980;
};

struct _metad {
    db_id_t id = 0;
    bool corrupt = false;
    bool allow = true;
};

struct tourist_t {
    _metad metadata;
    std::string surname;
    std::string name;
    std::string patronymic;
    unsigned short int passport_series = 0;
    unsigned int passport_number = 0;
    unsigned long long int phone_number = 0;
};

struct tour_t {
    _metad metadata;
    std::string town_from;
    std::string town_to;
    date date_start;
    date date_end;
    db_id_t manager = 0;
    std::vector<db_id_t> tourists;
};

struct employe_t {
    _metad metadata;
    std::string surname;
    std::string name;
    std::string patronymic;
    unsigned long long int phone_number = 0;
    roles role;
};

#endif /* __BASE_H__ */
