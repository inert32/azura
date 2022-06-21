#ifndef __DB_BASE_H__
#define __DB_BASE_H__

#include "base.h"
#include "io.h"

template<class T>
class db_base {
public:
    db_base(io_base<T>* _io);
    ~db_base();

    bool record_create(unparsed_t* rec);
    T* record_read(const db_id_t id);
    bool record_update(const unparsed_t* rec, const db_id_t id);
    bool record_delete(const db_id_t id);
    bool record_exists(const db_id_t id);

    bool db_sync();
    
    db_id_t db_size();
private:
    std::vector<T> arr;
    io_base<T>* io;
    std::vector<db_id_t> changed_records;

    bool have_changed = false;
    bool have_removed = false;
};

template<class T>
db_base<T>::db_base(io_base<T>* _io) { 
    io = _io;
    if (io == nullptr) return;
    db_id_t id = 0;
    while (true) {
        T tmp;
        auto i = io->read_record(&tmp, id);
        if (i == io_codes::eof) break;
		if (i == io_codes::struct_corrupt) tmp.metadata.corrupt = true;
		id++;
        arr.push_back(tmp);
    }
}

template<class T>
db_base<T>::~db_base() {
    db_sync();
}

template<class T>
db_id_t db_base<T>::db_size() {
    return arr.size();
}

template<class T>
bool db_base<T>::db_sync() {
    if (io == nullptr) return false;
    bool ret = true;
    if (have_removed) {
        io->have_removed();
        for (auto &r : arr) ret = io->write_record(&r, r.metadata.id);
	}
    else if (have_changed)
        for (auto &r : changed_records) ret = io->write_record(&arr[r], r);
    return ret;
}

template<class T>
T* db_base<T>::record_read(const db_id_t id) {
    try {
        return &arr.at(id);
    }
    catch (const std::exception &e) {
        return nullptr;
    }
}

template<class T>
bool db_base<T>::record_exists(const db_id_t id) {
    try {
        auto x = arr.at(id);
    } 
    catch (std::out_of_range&) {
        return false;
    }
    return true;
}

template<class T>
bool db_base<T>::record_create(unparsed_t* rec) {
    have_changed = true;
    T record;
    record.metadata.id = arr.size();

    parsers<T> parser;
    if (parser.validate(rec, &record, false) == false) record.metadata.corrupt = true;

    prettify_records<T> pr;
    pr.prettyify(&record);
    arr.push_back(record);
    changed_records.push_back(record.metadata.id);
    return true;
}

template<class T>
bool db_base<T>::record_delete(db_id_t id) {
    have_removed = true;
    arr.erase(arr.begin() + id);
    const size_t new_size = arr.size();
    for (auto i = id; i < new_size; ++i)
        arr[i].metadata.id = i;
    return true;
}

template<class T>
bool db_base<T>::record_update(const unparsed_t* rec, const db_id_t id) {
    have_changed = true;
    T record;
    record.metadata.id = id;

    parsers<T> parser;
    if (parser.validate(rec, &record, false) == false) record.metadata.corrupt = true;

    prettify_records<T> pr;
    pr.prettyify(&record);

    arr[id] = record;
    changed_records.push_back(id);
    return true;
}

#endif /* __DB_BASE_H__ */
