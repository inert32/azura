// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "parsers.h"

bool parser_tourist_t(std::string_view str, tourist_t* t) {
     std::string buf;
     size_t left = 0, right = str.find(','), field = 0;
     while (field < 7) {
          buf = str.substr(left, right - left);
          if (buf.empty()) return false;
          switch (field) {
          case 0:
               t->id = std::stoi(buf);
            break;
          case 1:
               t->surname = buf; 
            break;
          case 2:
               t->name = buf; 
            break;
          case 3:
               t->patronymic = buf; 
            break;
          case 4:
               t->passport_series = std::stoi(buf); 
            break;
          case 5:
               t->passport_number = std::stoi(buf); 
            break;
          case 6:
               t->phone_number = std::stoll(buf);
            break;
          default:
               break;
          }
          field++;
          left = right + 1;
          right = str.find(',', right + 1);
          if (right == -1) right = str.length();
     }
     return (!t->phone_number == 0) ? true : false;
}
bool parser_tours_t(std::string_view str, tour_t* t);
bool parser_employe_t(std::string_view str, employe_t* t);
