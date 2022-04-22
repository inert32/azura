// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <vector>
#include <string>
#include "../io.h"
#include "../db_base.h"

template <>
tourist_t* db_base<tourist_t>::record_get(const db_id_t id) {
    return (arr.size() > 0) ? &(arr[id]) : nullptr;
}

template <>
bool db_base<tourist_t>::record_add(tourist_t* rec) {
    rec->metadata.id = arr.size();
    arr.push_back(*rec);
    return true;
}

template <>
bool db_base<tourist_t>::record_del(db_id_t id) {
    arr.erase(arr.begin() + id);
    return true;
}

template <>
bool db_base<tourist_t>::record_edit(const tourist_t* rec, const db_id_t id) {
    arr[id] = *rec;
    return true;
}

template <>
bool db_base<tourist_t>::db_sync() {    
    for (auto &x : changed_records) 
        io->write_record(&arr[x], x);
    return true;
}