#ifndef __IO_H__
#define __IO_H__
#include <fstream>
#include <filesystem>
#include "base.h"

constexpr unsigned int file_line_length = 64;

enum class fio_codes {
	struct_complete,
	struct_corrupt,
	eof
};

/* Code results:
	* 0 - struct is complete
	* 1 - struct is corrupt
	* 2 - reached EOF
	*/

class file_io {
public:
    file_io(const std::filesystem::path &path);
    
    bool write_rec(const tourist_t* t);
    void read_rec(tourist_t* t, fio_codes* code);
    
    void wipe_file();
private:
    void resetfile();
    void _create_file(const std::filesystem::path &file_path);
    
    std::filesystem::path _file_path;
    std::fstream file_handle;
};
#endif
