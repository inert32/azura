#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <filesystem>
#include "secure.h"

void parse_cli(int argc, char** argv);

extern std::filesystem::path tourists_file_path;
extern std::filesystem::path tours_file_path;
extern std::filesystem::path employes_file_path;

extern secure_ctl* secure;

#endif /* __CONFIG_H__ */
