#ifndef __TOURIST_CTL_H__
#define __TOURIST_CTL_H__
#include "base.h"

struct tourist_t {
	id_t id;
	std::string surname;
	std::string name;
	std::string patronymic;
	unsigned short int passport_series;
	unsigned short int passport_number;
	unsigned int phone_number;
};

class tourist_ctl : record_ctl {
public:
	tourist_ctl(std::string file_path);
private:
	std::list<tourist_t> arr;
};

#endif __TOURIST_CTL_H__