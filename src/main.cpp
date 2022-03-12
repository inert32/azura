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
#include "io.h"
#include "parsers.h"
#include "ui/ui.h"

#include "db/tour_ctl.h"
#include "db/tourist_ctl.h"
#include "db/employe_ctl.h"

/* TODO List
tourist_ctl                 : 9/9 
tours_ctl                   : 0/9
employe_ctl                 : 0/9

min_tui                     : 4/5
curses_ui                   : 0/5
win_ui                      : 0/5

io                          : 0/6
parsers                     : 0/3

DB recovery                 : no
Backup before edit/remove   : no

*/

int main() {
    std::cout << "v0.02 " << std::endl
         << "Build date: " << __TIMESTAMP__ << std::endl;

	min_tui ui;
	ui.pause();
    try {
		ui.msg(std::filesystem::absolute("tourists.txt").generic_string());
		file_io tourists_file(std::filesystem::absolute("tourists.txt"));
        tourist_ctl t(&tourists_file);
        while (ui.main_cycle(&t)) {}
    }
    catch (const std::exception &e) {
        if (strcmp(e.what(),"Quit") == 0) return 0;
        std::cout << "Exception recieved: " << e.what() << std::endl;
        system("pause");
        return -1;
    }
    return 0;
}
