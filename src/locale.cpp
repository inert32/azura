// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "locale.h"

const std::string AZ_LOC_PROGNAME = "Azura";

const std::string AZ_LOC_MENU_MM = "Main";
const std::string AZ_LOC_MENU_ENTRY = "Record";
const std::string AZ_LOC_MENU_DB = "Database";

const std::string AZ_LOC_MENU_MM_SWUSER = "Switch user";
const std::string AZ_LOC_MENU_MM_SWTAB = "Switch table";
const std::string AZ_LOC_MENU_MM_QUIT = "Quit";
const std::string AZ_LOC_MENU_ENTRY_ADD = "New record";
const std::string AZ_LOC_MENU_ENTRY_EDIT = "Edit record";
const std::string AZ_LOC_MENU_ENTRY_REMOVE = "Remove record";
const std::string AZ_LOC_MENU_DB_NEW = "New DB";
const std::string AZ_LOC_MENU_DB_SAVE = "Save DB";
const std::string AZ_LOC_MENU_DB_BACKUP = "Backup DB";
const std::string AZ_LOC_MENU_DB_REMOVE = "Remove DB";

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
  AZ_LOC_TAB_PATRONYMIC, AZ_LOC_TAB_PHONE_NUMBER, AZ_LOC_TAB_ROLE };

const std::string AZ_LOC_ERR_EXCEPTION = "Exception occured";
const std::string AZ_LOC_ERR_NOFILE = "File unavaliable";
