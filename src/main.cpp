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
#include "config.h"

#include "io.h"
#include "parsers.h"

#include "db_base.h"

#include "ui/ui_min.h"

#include "locale.h"

/* TODO List
tourist_ctl                 : 9/9 

DB recovery                 : no
Backup before edit/remove   : no
*/

int main(int argc, char** argv) {
    parse_cli(argc, argv);
    auto ui = new min_ui();
    try {
        auto employes_io = new file_io<employe_t>(std::filesystem::absolute(employes_file_path));
        secure = new secure_ctl(employes_io);
        if (secure->need_admin()) ui->adduser(employes_io);
		else if (!ui->login()) {
			std::cout << "Login failed." << std::endl;
			return -1;
		}
        auto employes = new db_base<employe_t>(employes_io);

        auto tourists_io = new file_io<tourist_t>(std::filesystem::absolute(tourists_file_path));
        auto tourists = new db_base<tourist_t>(tourists_io);

        auto tours_io = new file_io<tour_t>(std::filesystem::absolute(tours_file_path));
        auto tours = new db_base<tour_t>(tours_io);

        while (ui->main(tourists, tours, employes)) {}
        
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

std::filesystem::path tourists_file_path = "tourists.txt";
std::filesystem::path tours_file_path = "tours.txt";
std::filesystem::path employes_file_path = "employes.txt";

void parse_cli(int argc, char** argv) {}