#ifndef __IO_H__
#define __IO_H__
#include <fstream>
#include <iostream>
#include <filesystem>
#include "base.h"
#include "locale.h"
#include "parsers.h"
constexpr unsigned int file_line_length = 64;

enum class io_codes {
    struct_complete,
    struct_corrupt,
    eof,
    denied
};

/* Code results:
    * 0 - struct is complete
    * 1 - struct is corrupt
    * 2 - reached EOF
    * 3 - access denied for this uid
    */

template<class T>
class io_base {
public:
    virtual io_codes read_record(T* rec) = 0;
    virtual bool write_record(const T* rec) = 0;

    virtual void sync() = 0;
};

template<class T>
class file_io : public io_base<T> {
public:
    file_io(const std::filesystem::path& path);
    ~file_io();
    
    io_codes read_record(T* rec);

    bool write_record(const T* rec);
    
    void sync();
private:
    std::filesystem::path _file_path;
    std::fstream file_handle;
    bool write_to_disk = false;
};

template<class T>
file_io<T>::file_io(const std::filesystem::path& path) {
    _file_path = path;

    int tries = 0; // Trying three times to open file
    while (tries < 3) {
        file_handle.open(path, std::ios::in | std::ios::out | std::ios::binary);
        if (!file_handle.good()) {
            // Recreating file
            file_handle.close();
            std::filesystem::remove(path);
            file_handle.open(path.c_str(), std::ios::out);
            file_handle.close();
        }
        else break;
        tries++;
    }
    if (tries == 3) throw std::runtime_error("File " + path.generic_string() + " unavaliable");
}

template<class T>
io_codes file_io<T>::read_record(T* rec) {
    std::string buf_str;

    std::getline(file_handle, buf_str);

    if (buf_str.empty()) return io_codes::eof;
    parsers<T> parser;

    return (parser.parse(buf_str, rec) == true) ? io_codes::struct_complete : io_codes::struct_corrupt;
}

template<class T>
void file_io<T>::sync() {
    file_handle.flush();
}

template<class T>
file_io<T>::~file_io() {
    file_handle.close();
}

#endif /* __IO_H__ */
