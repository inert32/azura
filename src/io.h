#ifndef __IO_H__
#define __IO_H__
#include <fstream>
#include <filesystem>
#include "base.h"
#include "parsers.h"

constexpr unsigned int file_line_length = 64;

class file_io {
public:
    file_io(const std::filesystem::path &path);
    
     bool write_rec(const tourist_t* t);
     bool write_rec(const tour_t* t);
     bool write_rec(const employe_t* t);
    
     bool read_rec(tourist_t* t);
     bool read_rec(tour_t* t);
     bool read_rec(employe_t* t);
    
     void wipe_file();
private:
     void resetfile();
    void _create_file(const std::filesystem::path &file_path);
    
     std::filesystem::path _file_path;
    std::fstream file_handle;
};

#endif
