#ifndef __TOUR_CTL_H__
#define __TOUR_CTL_H__

#include <string>
#include <filesystem>
#include "base.h"

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

class tour_ctl {
public:
	tour_ctl(std::filesystem::path file_path);
private:
	std::vector<tour_t> arr;
};

#endif