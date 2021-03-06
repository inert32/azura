// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "locale.h"

const std::string AZ_LOC_MENU_ENTRY_ADD = "New record";
const std::string AZ_LOC_MENU_ENTRY_EDIT = "Edit record";

const std::string AZ_LOC_TAB_ID = "id";
const std::string AZ_LOC_TAB_SURNAME = "Surname";
const std::string AZ_LOC_TAB_NAME = "Name";
const std::string AZ_LOC_TAB_PATRONYMIC = "Patronymic";
const std::string AZ_LOC_TAB_PASSPORT_NUMBER = "Passport number";
const std::string AZ_LOC_TAB_PASSPORT_SERIES = "Passport series";
const std::string AZ_LOC_TAB_PHONE_NUMBER = "Phone number";
const std::string AZ_LOC_TAB_TOWN_FROM = "Town from";
const std::string AZ_LOC_TAB_TOWN_TO = "Town to";
const std::string AZ_LOC_TAB_DATE_START = "Date start";
const std::string AZ_LOC_TAB_DATE_END = "Date end";
const std::string AZ_LOC_TAB_MANAGER = "Manager";
const std::string AZ_LOC_TAB_TOURISTS = "Tourists list";
const std::string AZ_LOC_TAB_ROLE = "Role";
const std::string AZ_LOC_TAB_PASSWD = "Password";

const std::string AZ_LOC_TABLIST_TOURIST_T[] = 
{ AZ_LOC_TAB_ID, AZ_LOC_TAB_SURNAME, AZ_LOC_TAB_NAME, 
  AZ_LOC_TAB_PATRONYMIC, AZ_LOC_TAB_PASSPORT_NUMBER,
  AZ_LOC_TAB_PASSPORT_SERIES, AZ_LOC_TAB_PHONE_NUMBER };
const std::string AZ_LOC_TABLIST_TOUR_T[] = 
{ AZ_LOC_TAB_ID, AZ_LOC_TAB_TOWN_FROM, AZ_LOC_TAB_TOWN_TO, 
  AZ_LOC_TAB_DATE_START, AZ_LOC_TAB_DATE_END,
  AZ_LOC_TAB_MANAGER, AZ_LOC_TAB_TOURISTS };
const std::string AZ_LOC_TABLIST_EMPLOYE_T[] = 
{ AZ_LOC_TAB_ID, AZ_LOC_TAB_SURNAME, AZ_LOC_TAB_NAME, 
  AZ_LOC_TAB_PATRONYMIC, AZ_LOC_TAB_PHONE_NUMBER, 
  AZ_LOC_TAB_ROLE, AZ_LOC_TAB_PASSWD };

const std::string AZ_LOC_ERR_EXCEPTION = "Exception occured";
const std::string AZ_LOC_ERR_NOFILE = "File unavaliable";

template<>
std::string tablist<tourist_t>::get(const short int line) {
    if (line < 7) return AZ_LOC_TABLIST_TOURIST_T[line];
    else return "";
}

template<>
std::string tablist<tour_t>::get(const short int line) {
    if (line < 7) return AZ_LOC_TABLIST_TOUR_T[line];
    else return "";
}

template<>
std::string tablist<employe_t>::get(const short int line) {
    if (line < 7) return AZ_LOC_TABLIST_EMPLOYE_T[line];
    else return "";
}
