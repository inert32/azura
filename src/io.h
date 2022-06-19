#ifndef __IO_H__
#define __IO_H__
#include <fstream>
#include <iostream>
#include <filesystem>
#include "base.h"
#include "parsers.h"

constexpr unsigned int file_field_length = 32;

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
    virtual io_codes read_record(T* rec, const db_id_t id = -1) = 0;
    virtual bool write_record(const T* rec, const db_id_t id = -1) = 0;
    virtual void sync() = 0;

    virtual bool is_empty() = 0;
    virtual bool is_read_only() = 0;

    virtual void have_removed() = 0;
};

template<class T>
class file_io : public io_base<T> {
public:
    file_io(const std::filesystem::path& path);
    ~file_io();
    
    io_codes read_record(T* rec, const db_id_t id = -1);
    bool write_record(const T* rec, const db_id_t id = -1);
    void sync();

    bool is_empty();
    bool is_read_only();

    void have_removed();
private:
    std::filesystem::path _file_path;
    std::fstream file_handle;
    bool write_to_disk = false;

    bool seek_line(const db_id_t line);
    void _write_rec(const T* rec);
    bool read_only = false;
};

template<class T>
bool file_io<T>::is_empty() {
	seek_line(0);
	file_handle.peek();
	bool eof = file_handle.eof();
	if (eof) file_handle.clear();
    return eof;
}

template<class T>
bool file_io<T>::is_read_only() {
	return read_only;
}

template<class T>
void file_io<T>::have_removed() {
	file_handle.close();
    std::filesystem::remove(_file_path);
    file_handle.open(_file_path, std::ios::in | std::ios::out | std::ios::binary);
}

template<class T>
file_io<T>::file_io(const std::filesystem::path& path) {
    _file_path = path;

    if (!std::filesystem::is_regular_file(path)) {
        std::filesystem::remove(path);
        file_handle.open(path, std::ios::out);
        file_handle.close();
    }
    file_handle.open(path, std::ios::in | std::ios::out | std::ios:: binary);
    
    if (!file_handle.good()) { // Try read-only
        read_only = true;
        file_handle.close();
        file_handle.open(path, std::ios::in | std::ios:: binary);

        if (!file_handle.good()) throw std::runtime_error("File " + path.generic_string() + " unavaliable");
    }
}

template<class T>
io_codes file_io<T>::read_record(T* rec, const db_id_t id) {
    if (id != -1) 
        if (!seek_line(id)) return io_codes::eof;

    std::string buf_str;
    std::getline(file_handle, buf_str);
    
    if (buf_str.empty()) {
        seek_line(0);
        return io_codes::eof;
    }
    parsers<T> parser;
    auto raw = parser.parse(buf_str);
    return (parser.validate(&raw, rec) == true) ? io_codes::struct_complete : io_codes::struct_corrupt;
}

template<class T>
bool file_io<T>::write_record(const T* rec, const db_id_t id) {
    if (read_only) return false;
	if (id != -1) seek_line(id);

	if (file_handle.good()) {
		_write_rec(rec);
		file_handle << std::endl;
		file_handle.flush();
		return true;
	}
	else return false;
}

template<class T>
bool file_io<T>::seek_line(const db_id_t line) {
	/* Offset creation rule: 
	* 7*file_field_length - number of fields in *_t structs * length of field
	* +7 - count of delims in line
	*/
	const auto off = line * (7 * file_field_length + 7);
	file_handle.seekg(off);
	file_handle.seekp(off);
    file_handle.clear();
	return file_handle.good();
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
