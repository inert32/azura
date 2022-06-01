#ifndef __DB_BASE_H__
#define __DB_BASE_H__

#include "base.h"
#include "io.h"

template<class T>
class db_base {
public:
    db_base(io_base<T>* _io);
    ~db_base();

    T* record_get(const db_id_t id);
    bool record_add(T* rec);
    bool record_del(const db_id_t id);
    bool record_edit(const T* rec, const db_id_t id);
    bool record_exists(const db_id_t id);

    //void sort(const int field)

    bool db_sync();
    
    db_id_t db_size();
protected:
    std::vector<T> arr;
    //std::vector<db_id_t> changed_records;
    io_base<T>* io;
};

template<class T>
db_base<T>::db_base(io_base<T>* _io) { 
    io = _io;
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
    for (auto &x : arr) {
		io->write_record(&x, x.metadata.id);
	}
    return true;
}

template<class T>
T* db_base<T>::record_get(const db_id_t id) {
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
bool db_base<T>::record_add(T* rec) {
    rec->metadata.id = arr.size();
    arr.push_back(*rec);
    //changed_records.push_back(rec->metadata.id);
    return true;
}

template<class T>
bool db_base<T>::record_del(db_id_t id) {
    arr.erase(arr.begin() + id);
    const size_t new_size = arr.size();
    for (auto i = id; i < new_size; ++i)
        arr[i].metadata.id = i;
    return true;
}

template<class T>
bool db_base<T>::record_edit(const T* rec, const db_id_t id) {
    arr[id] = *rec;
    //changed_records.push_back(id);
    return true;
}

#endif /* __DB_BASE_H__ */
