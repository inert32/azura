#ifndef __SECURE_H__
#define __SECURE_H__

#include "base.h"
#include "io.h"

enum class crud_actions {
	create,
	read,
	update,
	del
};

class secure_ctl {
public:
    secure_ctl(io_base<employe_t>* io);

    db_id_t get_uid();
    roles_enum get_role();

    bool need_admin();
    bool need_login();
    bool login(const db_id_t id, const std::string& passwd);
    bool useradd(const employe_t* user);
	std::string uname();
private:
    io_base<employe_t>* _io;
    db_id_t uid;
    roles_enum rid;
    bool logged_in;
	std::string username;

	void _login(const employe_t* user);
};

template <class T>
class secure_check {
public:
	bool check_access(const db_id_t id, const crud_actions);
};

/* Roles:
 * |---------------+---------+------------+-------------------+-----------|
 * | Role          | Role ID | tourist_t  | tour_t            | employe_t |
 * |---------------+---------+------------+-------------------+-----------|
 * | Group manager |    0    | if allowed | if id=manager id  |     no    |
 * |               |         | by tour    |                   |           |
 * |---------------+---------+------------+-------------------+-----------|
 * | Seller        |    1    |    RW      |       RO          | to id=0   |
 * |---------------+---------+------------+-------------------+-----------|
 * | Boss          |    2    |    RW      |       RW          |     RW    |
 * |---------------+---------+------------+-------------------+-----------|
*/
#endif /* __SECURE_H__ */
