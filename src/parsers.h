#ifndef __PARSERS_H__
#define __PARSERS_H__
#include <string>
#include <string_view>
#include "base.h"

bool parser_tourist_t(std::string_view str, tourist_t* t);
bool parser_tours_t(std::string_view str, tour_t* t);
bool parser_employe_t(std::string_view str, employe_t* t);

#endif
