#ifndef __LOCALE_H__
#define __LOCALE_H__

#include <string>
#include "base.h"

extern const std::string AZ_LOC_MENU_ENTRY_ADD;
extern const std::string AZ_LOC_MENU_ENTRY_EDIT;

extern const std::string AZ_LOC_TAB_ID;
extern const std::string AZ_LOC_TAB_SURNAME;
extern const std::string AZ_LOC_TAB_NAME;
extern const std::string AZ_LOC_TAB_PATRONYMIC;
extern const std::string AZ_LOC_TAB_PASSPORT_NUMBER;
extern const std::string AZ_LOC_TAB_PASSPORT_SERIES;
extern const std::string AZ_LOC_TAB_PHONE_NUMBER;
extern const std::string AZ_LOC_TAB_TOWN_FROM;
extern const std::string AZ_LOC_TAB_TOWN_TO;
extern const std::string AZ_LOC_TAB_DATE_START;
extern const std::string AZ_LOC_TAB_DATE_END;
extern const std::string AZ_LOC_TAB_MANAGER;
extern const std::string AZ_LOC_TAB_TOURISTS;
extern const std::string AZ_LOC_TAB_ROLE;
extern const std::string AZ_LOC_TAB_PASSWD;

extern const std::string AZ_LOC_TABLIST_TOURIST_T[];
extern const std::string AZ_LOC_TABLIST_TOUR_T[];
extern const std::string AZ_LOC_TABLIST_EMPLOYE_T[]; 

extern const std::string AZ_LOC_ERR_EXCEPTION;
extern const std::string AZ_LOC_ERR_NOFILE;

template<class T>
class tablist {
public: 
    std::string get(const short int line);
};

#endif /* __LOCALE_H__ */
