#ifndef __PARSERS_H__
#define __PARSERS_H__
#include "base.h"

template <class T>
class parsers {
    public:
    bool parse(const std::string& str, T* t);
    void parse_tourists_count(const std::string &str, std::vector<db_id_t>* list);
};

template <class T>
void parsers<T>::parse_tourists_count(const std::string &str, std::vector<db_id_t>* list) {
   size_t left = 0, right = str.find(',');
   while (true) {
      if (left > right) break;
      std::cerr << "left: " << left << "; right: " << right << std::endl;
      std::string buf = str.substr(left, right - left);
      std::cerr << "selected: " << buf << std::endl;
      if (!buf.empty()) list->push_back(std::stoull(buf));
      else break; // Stop if there is no more values

      left = right + 1;
		right = str.find(',', right + 1);
		if (right == str.npos) right = str.length();
   }
}

#endif /* __PARSERS_H__ */
