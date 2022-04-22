#ifndef __IO_H__
#define __IO_H__
#include <fstream>
#include <filesystem>
#include "base.h"

constexpr unsigned int file_line_length = 64;

enum class fio_codes {
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
    virtual fio_codes read_record(T* rec, const db_id_t id) = 0;
    virtual bool write_record(const T* rec, const db_id_t id) = 0;

    virtual void sync() = 0;
};

template<class T>
class file_io : public io_base<T> {
public:
    file_io(const std::filesystem::path &path);
	~file_io();
    
    fio_codes read_record(T* t, const db_id_t id);
    bool write_record(const T* rec, const db_id_t id);
    
    void sync();
private:
    void resetfile();
    void create_file(const std::filesystem::path &file_path);
    
    std::filesystem::path _file_path;
    std::fstream file_handle;
};
#endif /* __IO_H__ */
