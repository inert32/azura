// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "base.h"
#include "secure.h"
#include "config.h"

#include "io.h"
#include "parsers.h"

#include "db_base.h"

#include "ui/ui.h"

#include "locale.h"

int main(int argc, char** argv) {
    parse_cli(argc, argv);
    ui_global = new current_ui();
    try {
        auto employes_io = new file_io<employe_t>(employes_file_path);
        if (employes_io->is_read_only()) ui_global->msg("File " + employes_file_path.generic_string() + " is read-only");
        secure = new secure_ctl(employes_io);
        if (secure->need_admin() && !ui_global->adduser(employes_io)) {
            ui_global->err("Registration failed");

            delete employes_io;
			delete ui_global;
            delete secure;
        }
		else if (!ui_global->login()) {
			ui_global->err("Login failed");

            delete employes_io;
			delete ui_global;
            delete secure;
		}
        auto employes = new db_base<employe_t>(employes_io);

        auto tourists_io = new file_io<tourist_t>(tourists_file_path);
        if (tourists_io->is_read_only()) ui_global->msg("File " + tourists_file_path.generic_string() + " is read-only");
        auto tourists = new db_base<tourist_t>(tourists_io);

        auto tours_io = new file_io<tour_t>(tours_file_path);
        if (tours_io->is_read_only()) ui_global->msg("File " + tours_file_path.generic_string() + " is read-only");
        auto tours = new db_base<tour_t>(tours_io);

        ui_global->main(tourists, tours, employes);
        
        delete tourists;
        delete tours;
        delete employes;

        delete tourists_io;
        delete tours_io;
        delete employes_io;
    }
    catch (const std::exception &e) {
       ui_global->err(AZ_LOC_ERR_EXCEPTION + ' '  + e.what());
    }

    delete ui_global;
    delete secure;

    return 0;
}

std::filesystem::path tourists_file_path = "tourists.txt";
std::filesystem::path tours_file_path = "tours.txt";
std::filesystem::path employes_file_path = "employes.txt";

secure_ctl* secure = nullptr;
ui_base* ui_global = nullptr;

void parse_cli(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        std::string buf(argv[i]);
        std::string option = buf.substr(0, buf.find('='));
        std::string value = buf.substr(buf.find('=') + 1);

        if (option == "tourists") tourists_file_path = std::filesystem::absolute(option);
        if (option == "tours") tours_file_path = std::filesystem::absolute(option);
        if (option == "employes") employes_file_path = std::filesystem::absolute(option);
    }
}

std::string human_to_string(db_base<employe_t>* table, const db_id_t id) {
    std::string out = "(" + std::to_string(id) + ") ";
    auto t = table->record_read(id);
    if (t != nullptr)
        out += t->surname + ' ' + t->name + ' ' + t-> patronymic;
    else
        out = "Unknown";
    return out;
}
std::string human_to_string(db_base<tourist_t>* table, const db_id_t id) {
    std::string out = "(" + std::to_string(id) + ") ";
    auto t = table->record_read(id);
    if (t != nullptr)
        out += t->surname + ' ' + t->name + ' ' + t-> patronymic;
    else
        out = "Unknown";
    return out;
}