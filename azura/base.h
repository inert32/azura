#ifndef __BASE_H__
#define __BASE_H__

#include <string>
#include <filesystem>
#include <fstream>
#include <iomanip>

typedef unsigned long long int db_id_t;

struct date_t {
	unsigned char day;
	unsigned char month;
	unsigned int year;
};

void util_resetfile(std::fstream& f);

#include "tour_ctl.h"
#include "tourist_ctl.h"
#include "employe_ctl.h"

#endif