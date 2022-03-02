#ifndef __EMPLOYE_CTL_H__
#define __EMPLOYE_CTL_H__
#include "base.h"

struct employe_t {
	id_t id;
	std::string surname;
	std::string name;
	std::string patronymic;
	unsigned int phone_number;
};

class employe_ctl {
public:
	employe_ctl(std::string path);
private:
	std::list<employe_t> arr;
};

#endif __EMPLOYE_CTL_H__