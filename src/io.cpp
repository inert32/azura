// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <fstream>
#include <filesystem>
#include "io.h"
#include "parsers.h"
#include "base.h"

template<>
io_codes file_io<tourist_t>::read_record(tourist_t* rec) {
    std::string buf_str;

    std::getline(file_handle, buf_str);

    if (buf_str.empty()) return io_codes::eof;

    return (parse_tourist_t(buf_str, rec) == true) ? io_codes::struct_complete : io_codes::struct_corrupt;
}

template<>
bool file_io<tourist_t>::write_record(const tourist_t* rec) {
    if (file_handle.eof()) file_handle.clear();
    
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