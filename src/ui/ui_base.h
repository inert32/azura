#ifndef __UI_BASE_H__
#define __UI_BASE_H__

#include "../base.h"
#include "../db_base.h"

enum class tables_list {
    tourists,
    tours,
    employes,
    _quit
};

enum class ui_actions {
    record_create,
    record_update,
    record_delete,
    switch_table,
    quit
};

class ui_base {
public:
    virtual ~ui_base() = default;

    virtual void msg(const std::string& body) = 0;
    virtual void msg(const std::string& body, const std::string& head) = 0;
    virtual void main(db_base<tourist_t>* tourists, 
                      db_base<tour_t>* tours,
                      db_base<employe_t>* employes) = 0;
    
    virtual bool login() = 0;
    virtual bool adduser(io_base<employe_t>* employes) = 0;
};

extern ui_base* ui_global;

std::string human_to_string(db_base<employe_t>* table, const db_id_t id);
std::string human_to_string(db_base<tourist_t>* table, const db_id_t id);

#endif /* __UI_BASE_H__ */