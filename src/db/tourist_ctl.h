#ifndef __TOURIST_CTL_H__
#define __TOURIST_CTL_H__

#include "../base.h"
#include "../io.h"

class tourist_ctl {
public:
    /* tourist_ctl API:
    * tourist_t* record_get(id)              - Require id of the required record.
    *                                        - Return pointer to the record or nullptr if fail.
     *
    * bool record_make(record)               - Require tourist_t struct to write.
     *                                        - Return true if record created or false otherwise.
    * 
    * bool record_del(db_id_t)               - Require id of the required record.
    *                                        - Return true if record removed or false otherwise.
    * 
    * bool record_edit(db_id_t, tourist_t*)  - Require id of the old record and new record struct
    *                                        - Return true if record changed or false otherwise.
    * 
    * bool db_sync()                         - IMPLEMENTATION DEPENDS ON USED STORAGE (file, real db, etc)
    *                                        - Sync current tourist_t array with database on drive
    *                                        - Return true if array synced or false otherwise.
    * 
    * tourist_ctl(file_io*)                  - Require pointer to database interface (with functions read_rec(), write_rec())
    */
    tourist_t* record_get(const db_id_t id);
    bool record_make(tourist_t* record);
     bool record_del(db_id_t id);
     bool record_edit(db_id_t id, tourist_t* record);

     bool db_sync();
     db_id_t db_size();

     tourist_ctl(file_io* f);
    ~tourist_ctl();
private:
    std::vector<tourist_t> arr;
     file_io* io;
};

#endif
