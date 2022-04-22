#ifndef __DB_BASE_H__
#define __DB_BASE_H__

#include "base.h"
#include "io.h"

template <class T>
class db_base {
public:
    db_base(io_base<T>* _io)  { 
        io = _io; 
    }

    ~db_base();

    virtual T* record_get(const db_id_t id);
    virtual bool record_add(T* rec);
    virtual bool record_del(const db_id_t id);
    virtual bool record_edit(const T* rec, const db_id_t id);

    virtual bool db_sync();
    
    db_id_t db_size() {
        return arr.size();
    }
protected:
    std::vector<T> arr;
    std::vector<db_id_t> changed_records;
    io_base<T>* io;
};

#endif /* __DB_BASE_H__ */