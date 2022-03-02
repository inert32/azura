#include <fstream>
#include <filesystem>
#include <sstream>
#include "tourist_ctl.h"

tourist_ctl::tourist_ctl(std::string file_path) {
	file_handle.open(std::filesystem::absolute(file_path));
	if (!file_handle.good())
		throw except_types::io_failure;

}