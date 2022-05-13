// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <fstream>
#include <filesystem>
#include "io.h"
#include "parsers.h"
#include "base.h"
#include "secure.h"

template<>
bool file_io<tourist_t>::write_record(const tourist_t* rec) {
    if (!write_to_disk) {
        file_handle.close();
        file_handle.open(_file_path, std::ios::out | std::ios::binary);
        write_to_disk = true;
    }
    
    if (file_handle.eof()) file_handle.clear();
    
    if (file_handle.good()) {
        file_handle.width(file_line_length);
        file_handle << rec->metadata.id << ',';
        file_handle.width(file_line_length);
        file_handle << rec->surname << ',';
        file_handle.width(file_line_length);
        file_handle << rec->name << ',';
        file_handle.width(file_line_length);
        file_handle << rec->patronymic << ',';
        file_handle.width(file_line_length);
        file_handle << rec->passport_series << ',';
        file_handle.width(file_line_length);
        file_handle << rec->passport_number << ',';
        file_handle.width(file_line_length);
        file_handle << rec->phone_number << std::endl;
        file_handle.flush();
        return true;
    }
    else return false;
}

template<>
bool file_io<tour_t>::write_record(const tour_t* rec) {
    if (!write_to_disk) {
        file_handle.close();
        file_handle.open(_file_path, std::ios::out | std::ios::binary);
        write_to_disk = true;
    }
    
    if (file_handle.eof()) file_handle.clear();
    
    if (file_handle.good()) {
        file_handle.width(file_line_length);
        file_handle << rec->metadata.id << ',';
        file_handle.width(file_line_length);
        file_handle << rec->town_from << ',';
        file_handle.width(file_line_length);
        file_handle << rec->town_to << ',';
        file_handle.width(file_line_length);
        file_handle << rec->date_start << ',';
        file_handle.width(file_line_length);
        file_handle << rec->date_end << ',';
        file_handle.width(file_line_length);

        const auto count = rec->tourists.size();
        for (size_t i = 0; i < count; i++) {
            file_handle << rec->tourists[i];
            if (i + 1 < count) file_handle << ',';
        }
        file_handle << std::endl;
        file_handle.flush();
        return true;
    }
    else return false;
}

template<>
bool file_io<employe_t>::write_record(const employe_t* rec) {
    if (!write_to_disk) {
        file_handle.close();
        file_handle.open(_file_path, std::ios::out | std::ios::binary);
        write_to_disk = true;
    }
    
    if (file_handle.eof()) file_handle.clear();
    
    if (file_handle.good()) {
        file_handle.width(file_line_length);
        file_handle << rec->metadata.id << ',';
        file_handle.width(file_line_length);
        file_handle << rec->surname << ',';
        file_handle.width(file_line_length);
        file_handle << rec->name << ',';
        file_handle.width(file_line_length);
        file_handle << rec->patronymic << ',';
        file_handle.width(file_line_length);
        file_handle << rec->phone_number << ',';
        file_handle.width(file_line_length);
        file_handle << rec->role << std::endl;
        file_handle.flush();
        return true;
    }
    else return false;
}
