#ifndef __IO_H__
#define __IO_H__
#include <fstream>
#include <iostream>
#include <filesystem>
#include "base.h"
#include "locale.h"
#include "parsers.h"

#define _goto_line(skip) \
    db_id_t lines = 0; \
    while (lines != (skip)) { \
        char c; \
        file_handle.read(&c, 1); \
        if (c == '\n') lines++; \
    }

#define resetfile() \
    file_handle.clear(); \
    file_handle.seekg(0); \
    file_handle.seekp(0);


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
    virtual io_codes read_record(T* rec, const db_id_t id) = 0;
    virtual bool write_record(const T* rec, const db_id_t id) = 0;

    virtual void sync() = 0;
};

template<class T>
class file_io : public io_base<T> {
public:
    file_io(const std::filesystem::path& path) {
        _file_path = path;

        int tries = 0; // Trying three times to open file
        while (tries < 3) {
            file_handle.open(path, std::ios::in | std::ios::out | std::ios::binary);
            if (!file_handle.good()) {
                file_handle.close();
                std::filesystem::remove(path);
                file_handle.open(path.c_str(), std::ios::out);
                file_handle.close();
            }
            else break;
            tries++;
        }
        if (tries == 3) throw;
    }
	~file_io() {
        file_handle.flush();
        file_handle.close();
    }
    
    io_codes read_record(T* rec, const db_id_t id);

    bool write_record(const T* rec, const db_id_t id);
    
    void sync() {
        file_handle.flush();
    }
private:
    std::filesystem::path _file_path;
    std::fstream file_handle;
};
#endif /* __IO_H__ */
