// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include "tourist_ctl.h"

void tourist_ctl::init(const std::filesystem::path &file_path) {
	file_handle.open(file_path, std::ios::in | std::ios::out | std::ios::binary);
	if (!file_handle.good()) {// Stop if file not found/unaccessible
		std::string str = file_path.string();
		throw std::filesystem::filesystem_error::exception(str);
	}

	while (!file_handle.eof()) {
		tourist_t buf;
		std::string buf_str = "";
		bool str_good = true;

		std::getline(file_handle, buf_str);
		if (buf_str.empty()) continue;

		str_good = _split_str(buf_str, &buf); // Sanity check for this string will be performed in _split_str()
		if (!str_good) 
			throw except_types::file_corrupt;

		arr.push_back(buf); // finally
		if (file_handle.eof()) break;
	}
}

tourist_ctl::~tourist_ctl() {
	file_handle.flush();
	file_handle.close();
}

bool tourist_ctl::_split_str(const std::string &str, tourist_t* t) {
	std::string buf;
	/*
	*  Left and right ends for substring,
	*  sw - current field in structure
	*/
	size_t left = 0, right = str.find(','), sw = 0;
	while (sw < 7) {
		buf = str.substr(left, right - left);
		if (buf.empty()) return false;
		switch (sw) {
		case 0:
			t->id = std::stoi(buf); break;
		case 1:
			t->surname = buf; break;
		case 2:
			t->name = buf; break;
		case 3:
			t->patronymic = buf; break;
		case 4:
			t->passport_series = buf; break;
		case 5:
			t->passport_number = buf; break;
		case 6:
			t->phone_number = buf; break;
		default:
			break;
		}
		sw++;
		left = right + 1;
		right = str.find(',', right + 1);
		if (right == -1) right = str.length();
	}
	return (!t->phone_number.empty()) ? true : false;
}

id_t tourist_ctl::update() {
	return arr.size();
}

tourist_t* tourist_ctl::get(const id_t id) {
	return (arr.size() > 0) ? &(arr[id]) : nullptr;
}

bool tourist_ctl::create(tourist_t* record) {
	record->id = arr.size();
	file_handle.seekp(0, file_handle.end);
	file_handle
		<< std::endl << record->id 
		<< ',' << record->surname
		<< ',' << record->name 
		<< ',' << record->patronymic
		<< ',' << record->passport_series 
		<< ',' << record->passport_number
		<< ',' << record->phone_number;
	file_handle.flush();
	return true;
}

bool tourist_ctl::remove(id_t id) {
	return true;
}
bool tourist_ctl::edit(id_t id, tourist_t* record) {
	return true;
}