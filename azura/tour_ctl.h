#ifndef __TOUR_CTL_H__
#define __TOUR_CTL_H__
#include "base.h"

struct tour_t {
	id_t id;
	std::string town_from;
	std::string town_to;
	date_t date_start;
	date_t date_end;
	id_t manager;
	unsigned int tourists_count;
	id_t* tourists;
};

class tour_ctl {
public:
	tour_ctl(std::string path);
private:
	std::list<tour_t> arr;
};

#endif __TOUR_CTL_H__