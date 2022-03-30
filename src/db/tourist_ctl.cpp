// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <vector>
#include <string>
#include "../io.h"
#include "tourist_ctl.h"

tourist_ctl::tourist_ctl(file_io* f) {
	io = f;
	while (true) {
		fio_codes code;
		tourist_t buf;
		io->read_rec(&buf, &code);
		buf.id = arr.size();
		if (code == fio_codes::eof) break;
		if (code == fio_codes::struct_corrupt)
			buf._corrupt = true;
		arr.push_back(buf);
	}
}

tourist_ctl::~tourist_ctl() {
    db_sync();
}

db_id_t tourist_ctl::db_size() {
    return arr.size();
}

bool tourist_ctl::db_sync() {
    io->wipe_file();
    
    for (auto &x : arr) io->write_rec(&x);
    
    return true;
}

tourist_t* tourist_ctl::record_get(const db_id_t id) {
    return (arr.size() > 0) ? &(arr[id]) : nullptr;
}

bool tourist_ctl::record_make(tourist_t* record) {
    record->id = arr.size();
    arr.push_back(*record);
    return true;
}

bool tourist_ctl::record_del(db_id_t id) {
    arr.erase(arr.begin() + id);
    return true;
}

bool tourist_ctl::record_edit(db_id_t id, tourist_t* record) {
    arr[id] = *record;
    return true;
}
