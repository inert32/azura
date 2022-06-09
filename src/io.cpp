// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "io.h"

template<>
void file_io<tourist_t>::_write_rec(const tourist_t* rec) {
	for (int field = 0; field < 7; field++) {
		file_handle.width(file_field_length);
		switch (field) {
		case 0:
			file_handle << rec->metadata.id << ',';
			break;
		case 1:
			file_handle << rec->surname << ',';
			break;
		case 2:
			file_handle << rec->name << ',';
			break;
		case 3:
			file_handle << rec->patronymic << ',';
			break;
		case 4:
			file_handle << rec->passport_series << ',';
			break;
		case 5:
			file_handle << rec->passport_number << ',';
			break;
		case 6:
			file_handle << rec->phone_number;
			break;
		}
	}
}

template<>
void file_io<tour_t>::_write_rec(const tour_t* rec) {
	for (int field = 0; field < 7; field++) {
		file_handle.width(file_field_length);
		switch (field) {
		case 0:
			file_handle << rec->metadata.id << ',';
			break;
		case 1:
			file_handle << rec->town_from << ',';
			break;
		case 2:
			file_handle << rec->town_to << ',';
			break;
		case 3:
			file_handle << rec->date_start << ',';
			break;
		case 4:
			file_handle << rec->date_end << ',';
			break;
		case 5:
			file_handle << rec->manager << ',';
			break;
		case 6: {
			const auto count = rec->tourists.size();
			std::string out;
			for (size_t i = 0; i < count; i++) {
				out += std::to_string(rec->tourists[i]);
				if (i + 1 < count) out += ';';
			}
			file_handle << out;
			break;
		}
		}
	}
}

template<>
void file_io<employe_t>::_write_rec(const employe_t* rec) {
    for (int field = 0; field < 7; field++) {
        file_handle.width(file_field_length);
        switch (field) {
        case 0:
            file_handle << rec->metadata.id << ',';
            break;
        case 1:
            file_handle << rec->surname << ',';
            break;
        case 2:
            file_handle << rec->name << ',';
            break;
        case 3:
            file_handle << rec->patronymic << ',';
            break;
        case 4:
            file_handle << rec->phone_number << ',';
            break;
        case 5:
            file_handle << (int)rec->role << ',';
            break;
        case 6:
            file_handle << rec->passwd;
            break;
        }
    }
}