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
tourist_ctl            : 9/9 
tours_ctl             : 0/9
employe_ctl            : 0/9

min_tui              : 5/5
curses_ui             : 0/5
win_ui               : 0/5

io                 : 2/6
parsers              : 1/3

DB recovery            : no
Backup before edit/remove   : no

*/

int main() {
    az_ui ui;
    
    try {
       file_io tourists_file(std::filesystem::absolute("tourists.txt"));
       //file_io tours_file(std::filesystem::absolute("tours.txt"));
       tourist_ctl tourists(&tourists_file);
       //tour_ctl tours(&tours_file);
       while (ui.main_cycle(&tourists)) {}
    }
    catch (const std::exception &e) {
       if (strcmp(e.what(),"Quit") == 0) return 0;
       std::cout << "Exception recieved: " << e.what() << std::endl;
       system("pause");
       return -1;
    }
    return 0;
}
