#ifndef __TOURIST_CTL_H__
#define __TOURIST_CTL_H__
#include "base.h"

struct tourist_t {
	id_t id = 0;
	std::string surname = "";
	std::string name = "";
	std::string patronymic = "";
	std::string passport_series = "";
	std::string passport_number = "";
	std::string phone_number = "";
};

class tourist_ctl {
public:
	/* tourist_ctl API:
	* tourist_ctl() - Require path to the file
	* get() - Require id of the record.
	*       - Return pointer to the record or nullptr if fail.
	
	*/
	tourist_t* get(const id_t id);
	id_t update();
	bool create(tourist_t* record);
	bool remove(id_t id);
	bool edit(id_t id, tourist_t* record);
	void init(const std::filesystem::path &file_path);

	tourist_ctl() = default;
	~tourist_ctl();
private:
	std::vector<tourist_t> arr;
	bool _split_str(const std::string& str, tourist_t* t);
	std::fstream file_handle;
};

#endif __TOURIST_CTL_H__