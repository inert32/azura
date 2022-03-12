#include <fstream>
#include <filesystem>
#include "io.h"
#include "parsers.h"
#include "base.h"

file_io::file_io(const std::filesystem::path &path) {
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

	file_handle << t->id
		<< ',' << t->surname
		<< ',' << t->name
		<< ',' << t->patronymic
		<< ',' << t->passport_series
		<< ',' << t->passport_number
		<< ',' << t->phone_number;

	file_handle << std::endl;
	file_handle.flush();
	return true;
}

bool file_io::read_rec(tourist_t* t) {
    /* Outcomes:
     * return true - struct is complete
     * return false - struct is corrupt/reached EOF
     */
	std::string buf_str = "";

    std::getline(file_handle, buf_str);

	return parser_tourist_t(buf_str, t);
}
