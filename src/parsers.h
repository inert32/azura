#ifndef __PARSERS_H__
#define __PARSERS_H__
#include "base.h"

bool parser_tourist_t(const std::string &str, tourist_t* t);
bool parser_tours_t(const std::string &str, tour_t* t);
bool parser_employe_t(const std::string &str, employe_t* t);

#endif
