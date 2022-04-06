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

#include "db/tour_ctl.h"
#include "db/tourist_ctl.h"
#include "db/employe_ctl.h"

#include "ui/ui.h"

/* TODO List
tourist_ctl                 : 9/9 
tours_ctl                   : 0/9
employe_ctl                 : 0/9

min_tui                     : 5/5
curses_ui                   : 0/5
win_ui                      : 0/5

io                          : 2/6
parsers                     : 1/3

DB recovery                 : no
Backup before edit/remove   : no

*/

bool ui_ctl::initdb() {
    try {
        file_io tourists_file(std::filesystem::absolute("tourists.txt"));
        //file_io tours_file(std::filesystem::absolute("tours.txt"));
        
        tourists = new tourist_ctl(&tourists_file);
        //tour_ctl b(&tours_file);
    }
    catch (const std::exception &e) {
        msg("Exception recieved", e.what());
        return false;
    }
    return true;
}

#ifdef AZ_UI_MIN
int main(int argc, char** argv) {
    min_ui ui;
    ui.login();
    if (ui.initdb())
        while (ui.main_cycle()) {}
    return 0;
}
#endif /* AZ_UI_MIN */
