#ifndef __PARSERS_H__
#define __PARSERS_H__
#include "base.h"

template <class T>
class parsers {
    public:
    bool parse(const std::string& str, T* t);
    db_id_t* parse_tourists_count(const std::string &str, size_t* count);
};

template <class T>
db_id_t* parsers<T>::parse_tourists_count(const std::string &str, size_t* count) {
   // Get count first
   size_t left = 0, right = str.find(','); *count = 0;
   while (right != str.npos) {
      left = right + 1;
      right = str.find(',', right + 1);
      (*count)++;
   }
   auto list = new db_id_t[(*count)]; size_t i = 0;
   for (; i < *count; i++) list[i] = 0;

   // Append ids
   left = 0, right = str.find(',', 0);
   while (right != str.npos) {
      std::string buf = str.substr(left, right - left);
      if (!buf.empty()) list[i++] = std::stoull(buf);
      else break;
      left = right + 1;
      right = str.find(',', right + 1);
   }
   return list;
}

#endif /* __PARSERS_H__ */
