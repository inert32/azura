// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <fstream>
#include <filesystem>
#include "io.h"
#include "parsers.h"
#include "base.h"

#define _goto_line(skip) \
    db_id_t lines = 0; \
    while (lines != (skip)) { \
        char c; \
        file_handle.read(&c, 1); \
        if (c == '\n') lines++; }

template<class T>
file_io<T>::file_io(const std::filesystem::path& path) {
    _file_path = path;

    int tries = 0;
    while (tries < 3) {
        file_handle.open(path, std::ios::in | std::ios::out | std::ios::binary);
        if (!file_handle.good()) {
            file_handle.close();
            std::filesystem::remove(path);
            file_handle.open(path.c_str(), std::ios::out);
            file_handle.close();
            file_handle.open(path, std::ios::in | std::ios::out | std::ios::binary);
        }
        else break;
        tries++;
    }
    if (tries == 3) throw std::filesystem::filesystem_error("Can't open file " + path.string());
}

template<class T>
file_io<T>::~file_io() {
    file_handle.flush();
    file_handle.close();
}

template<class T>
void file_io<T>::resetfile() {
    file_handle.clear();
    file_handle.seekg(0);
    file_handle.seekp(0);
}

template<>
bool file_io<tourist_t>::write_record(const tourist_t* rec, const db_id_t id) {
    if (file_handle.eof()) file_handle.clear();
    _goto_line(id);
    
    if (file_handle.good()) {
        file_handle.width(64);
        file_handle << rec->metadata.id << ',';
        file_handle.width(64);
        file_handle << rec->surname << ',';
        file_handle.width(64);
        file_handle << rec->name << ',';
        file_handle.width(64);
        file_handle << rec->patronymic << ',';
        file_handle.width(64);
        file_handle << rec->passport_series << ',';
        file_handle.width(64);
        file_handle << rec->passport_number << ',';
        file_handle.width(64);
        file_handle << rec->phone_number << std::endl;
        file_handle.flush();
        return true;
    }
    else return false;
}

template<>
fio_codes file_io<tourist_t>::read_record(tourist_t* rec, const db_id_t id) {
    std::string buf_str;

    _goto_line(id);

    std::getline(file_handle, buf_str);

	if (buf_str.empty()) return fio_codes::eof;

	return (parser_tourist_t(buf_str, rec) == true) ? fio_codes::struct_complete : fio_codes::struct_corrupt;
}