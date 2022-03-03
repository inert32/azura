#ifndef __BASE_H__
#define __BASE_H__

typedef unsigned long long int id_t;

struct date_t {
	unsigned char day;
	unsigned char month;
	unsigned int year;
};

enum except_types {
	_null,
	io_failure,
	file_corrupt
};

#endif __BASE_H__