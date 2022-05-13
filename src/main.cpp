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
#include <limits>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "base.h"
#include "secure.h"

#include "io.h"
#include "parsers.h"

#include "db_base.h"

#include "ui/ui_min.h"

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

int main(int argc, char** argv) {
    auto ui = new min_ui();
    try {
        auto tourists_io = new file_io<tourist_t>(std::filesystem::absolute("tourists.txt"));
        auto tourists = new db_base<tourist_t>(tourists_io);

        auto tours_io = new file_io<tour_t>(std::filesystem::absolute("tours.txt"));
        auto tours = new db_base<tour_t>(tours_io);

        auto employes_io = new file_io<employe_t>(std::filesystem::absolute("employes.txt"));
        auto employes = new db_base<employe_t>(employes_io);
        
        std::cerr << "Main cycle\n";

        while (ui->main(tourists, tours, employes)) {}
        
        std::cerr << "Leaving" << std::endl;
        
        delete tourists;
        delete tours;
        delete employes;

        delete tourists_io;
        delete tours_io;
        delete employes_io;
    }
    catch (const std::exception &e) {
       ui->msg(AZ_LOC_ERR_EXCEPTION + ' '  + e.what());
       return -1;
    }

    return 0;
}
