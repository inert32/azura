#ifndef __TOURIST_CTL_H__
#define __TOURIST_CTL_H__

#include "base.h"

struct tourist_t {
	db_id_t id = 0;
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
	* record_get()  - Require id of the record.
	*               - Return pointer to the record or nullptr if fail.
	* 
	*/
	tourist_t* record_get(const db_id_t id);
	db_id_t arr_update();
	db_id_t arr_size();
	bool record_make(tourist_t* record);
	bool record_del(db_id_t id);
	bool record_edit(db_id_t id, tourist_t* record);

	tourist_ctl(const std::filesystem::path &path);
	~tourist_ctl();
private:
	std::fstream file_handle;
	std::filesystem::path file_path;
	std::vector<tourist_t> arr;
	bool _split_str(const std::string& str, tourist_t* t);
	void _write_ln(const tourist_t* t, const db_id_t line = -1);
};

#endif
