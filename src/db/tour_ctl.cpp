// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <vector>
#include <string>
#include "../io.h"
#include "tour_ctl.h"

tour_ctl::tour_ctl(file_io* f) {
	io = f;
	while (true) {
		fio_codes code;
		tourist_t buf;
		io->read_rec(&buf, &code);
		if (code == fio_codes::eof) break;
		arr.push_back(buf);
	}
}

tour_ctl::~tour_ctl() {
    db_sync();
}

db_id_t tour_ctl::db_size() {
    return arr.size();
}

bool tour_ctl::db_sync() {
    io->wipe_file();

    for (auto &x : arr) io->write_rec(&x);

    return true;
}

tourist_t* tour_ctl::record_get(const db_id_t id) {
    return (arr.size() > 0) ? &(arr[id]) : nullptr;
}

bool tour_ctl::record_make(tourist_t* record) {
    record->id = arr.size();
    arr.push_back(*record);
    return true;
}

bool tour_ctl::record_del(db_id_t id) {
    arr.erase(arr.begin() + id);
    return true;
}

bool tour_ctl::record_edit(db_id_t id, tourist_t* record) {
    arr[id] = *record;
    return true;
}