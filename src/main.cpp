// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <string>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <iomanip>

#include "base.h"
#include "secure.h"

#include "io.h"
#include "parsers.h"

#include "db_base.h"

#include "ui/ui_wx.h"

#include "locale.h"

/* TODO List
tourist_ctl                 : 9/9 
tours_ctl                   : 0/9
employe_ctl                 : 0/9

min_tui                     : 5/5

io                          : 2/6
parsers                     : 1/3

DB recovery                 : no
Backup before edit/remove   : no
*/

IMPLEMENT_APP(wx_gui);
IMPLEMENT_WX_THEME_SUPPORT;