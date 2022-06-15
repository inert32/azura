// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "secure.h"

secure_ctl::secure_ctl(io_base<employe_t>* io) {
    _io = io;
    logged_in = false;
    uid = -1;
    rid = roles_enum::guide;
}

db_id_t secure_ctl::get_uid() {
    return uid;
}

bool secure_ctl::login(const db_id_t id, const std::string& passwd) {
    employe_t buf;
	auto i = _io->read_record(&buf, id);
	if (i != io_codes::struct_complete) return false;

    if (buf.metadata.id == id && buf.passwd == passwd) {
		_login(&buf);
        return true;
    }
    return false;
}

std::string secure_ctl::uname() {
	return username;
}

void secure_ctl::_login(const employe_t* user) {
	uid = user->metadata.id;
	rid = user->role;
	logged_in = true;
	username = user->surname + ' ' + user->name + ' ' + user->patronymic;
}

bool secure_ctl::need_admin() {
	return _io->is_empty();
}

bool secure_ctl::need_login() {
    return !logged_in;
}

bool secure_ctl::useradd(const employe_t* user) {
    if (_io->write_record(user)) {
        _io->sync();
		_login(user);
        return true;
    }
    else return false;
}