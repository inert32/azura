// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <fstream>
#include <filesystem>
#include "io.h"
#include "parsers.h"
#include "base.h"

file_io::file_io(const std::filesystem::path& path) {
    _file_path = path;
    _create_file(_file_path);
}

void file_io::_create_file(const std::filesystem::path& file_path) {
    file_handle.open(file_path, std::ios::in | std::ios::out | std::ios::binary);
    if (!file_handle.good()) wipe_file();
}

void file_io::resetfile() {
    file_handle.clear();
    file_handle.seekg(0);
    file_handle.seekp(0);
}

void file_io::wipe_file() {
    file_handle.close();
    std::filesystem::remove(_file_path);
    file_handle.open(_file_path.c_str(), std::ios::out);
    file_handle.close();
    file_handle.open(_file_path, std::ios::in | std::ios::out | std::ios::binary);
}

bool file_io::write_rec(const tourist_t* t) {
    if (file_handle.eof()) file_handle.clear();
    file_handle.seekp(0, file_handle.end);

    file_handle.width(64);
    file_handle << t->surname << ',';
    file_handle.width(64);
    file_handle << t->name << ',';
    file_handle.width(64);
    file_handle << t->patronymic << ',';
    file_handle.width(64);
    file_handle << t->passport_series << ',';
    file_handle.width(64);
    file_handle << t->passport_number << ',';
    file_handle.width(64);
    file_handle << t->phone_number << std::endl;
    file_handle.flush();
    return true;
}

void file_io::read_rec(tourist_t* t, fio_codes* code) {
    
    std::string buf_str;

    std::getline(file_handle, buf_str);

	if (buf_str.empty()) {
		*code = fio_codes::eof;
		return;
	}

	*code = (parser_tourist_t(buf_str, t) == true) ? fio_codes::struct_complete : fio_codes::struct_corrupt;
}
