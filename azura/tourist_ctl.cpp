// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include "tourist_ctl.h"

tourist_ctl::tourist_ctl(const std::filesystem::path &path) {
	file_path = path;
	file_handle.open(file_path, std::ios::in | std::ios::out | std::ios::binary);
	if (!file_handle.good()) {
		// Trying to create and reopen file
		file_handle.close();
		file_handle.open(file_path, std::ios::out);
		if (!file_handle.good()) // Stop if file unaccessible
			throw std::filesystem::filesystem_error::exception("Inaccesible file");
		else {
			file_handle.close();
			file_handle.open(file_path, std::ios::in | std::ios::out | std::ios::binary);
		}
	}
	file_handle.width(64);
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

db_id_t tourist_ctl::arr_size() {
	return arr.size();
}

db_id_t tourist_ctl::arr_update() {
	util_resetfile(file_handle);
	arr.erase(arr.begin(), arr.end());
	while (!file_handle.eof()) {
		tourist_t buf;
		std::string buf_str = "";
		bool str_good = true;

		std::getline(file_handle, buf_str);
		if (buf_str.empty()) continue;

		// Sanity check for this string will be performed in _split_str()
		str_good = _split_str(buf_str, &buf);
		if (!str_good)
			throw std::length_error("File corrupt");

		arr.push_back(buf); // finally
		if (file_handle.eof()) break;
	}
	return arr.size();
}

tourist_t* tourist_ctl::record_get(const db_id_t id) {
	return (arr.size() > 0) ? &(arr[id]) : nullptr;
}

bool tourist_ctl::record_make(tourist_t* record) {
	record->id = arr.size();
	_write_ln(record);
	return true;
}

bool tourist_ctl::record_del(db_id_t id) {
	file_handle.close();
	std::filesystem::remove(file_path);
	file_handle.open(file_path, std::ios::out);

	db_id_t new_id = 0;

	arr.erase(arr.begin() + id);
	for (auto &i : arr) {
		auto record = &i;
		record->id = new_id;
		_write_ln(record);
		new_id++;
	}
	file_handle.flush();
	file_handle.close();
	file_handle.open(file_path, std::ios::in | std::ios::out | std::ios::binary);
	file_handle.width(64);
	return true;
}

bool tourist_ctl::record_edit(db_id_t id, tourist_t* record) {
	_write_ln(record, id);
	return true;
}

void tourist_ctl::_write_ln(const tourist_t* t, const db_id_t line) {
	util_resetfile(file_handle);
	if (line == -1)
		file_handle.seekp(0, file_handle.end);
	else {
		db_id_t line_skip = 0;
		while (line_skip != line) {
			char c;
			file_handle.read(&c, 1);
			if (c == '\n') line_skip++;
		}
		file_handle.seekp(file_handle.tellg());
	}

	file_handle << t->id
		<< ',' << t->surname
		<< ',' << t->name
		<< ',' << t->patronymic
		<< ',' << t->passport_series
		<< ',' << t->passport_number
		<< ',' << t->phone_number
		<< std::endl;
	file_handle.flush();
}
