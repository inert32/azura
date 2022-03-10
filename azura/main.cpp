// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <string>
#include <iomanip>

#include "base.h"

#include "ui.h"

/* TODO List
tourist_ctl                 : 9/9 
tours_ctl                   : 0/9
employe_ctl                 : 0/9

min_tui                     : 4/5
curses_ui                   : 0/5
win_ui                      : 0/5

DB recovery                 : no
Backup before edit/remove   : no

*/

int main() {
	std::cout << "v0.02 " << std::endl
		 << "Build date: " << __TIMESTAMP__ << std::endl;

	try {
		min_tui ui;
		tourist_ctl t(std::filesystem::absolute("tourists.txt"));
		while (true) {
			ui.draw_table(&t);
			ui.choose(&t);
		}
	}
	catch (const std::exception &e) {
		if (strcmp(e.what(),"Quit") == 0) return 0;
		std::cout << "Exception recieved: " << e.what() << std::endl;
		system("pause");
		return -1;
	}
	
	system("pause");
	return 0;
}

void util_resetfile(std::fstream& f) {
	f.clear();
	f.seekg(0);
	f.seekp(0);
}