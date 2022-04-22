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

#include "ui/ui.h"
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

start() {
	AZ_CURRENT_UI ui;
    ui.login();
	try {
		//file_io tours_file(std::filesystem::absolute("tours.txt"));
		file_io<tourist_t> tourists_file(std::filesystem::absolute("tourists.txt"));

		auto tourists = new db_base<tourist_t>(&tourists_file);
		ui.get_tables(tourists, nullptr, nullptr);
		ui.main();
	}
	catch (const std::exception &e) {
		ui.msg(AZ_LOC_ERR_EXCEPTION, e.what());
		return -1;
	}
    return 0;
}