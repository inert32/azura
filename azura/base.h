#ifndef __BASE_H__
#define __BASE_H__

#include <string>
#include <list>

typedef unsigned long long int id_t;

struct date_t {
	unsigned char day;
	unsigned char month;
	unsigned int year;
};

class record_ctl {
public:
	virtual void get(id_t id);
	virtual void get(id_t begin, id_t end);
	virtual void create(id_t id);
	virtual void remove(id_t id);
	virtual void edit(id_t id);
protected:
	std::fstream file_handle;
};

enum except_types {
	io_failure
};

#endif __BASE_H__