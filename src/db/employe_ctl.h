#ifndef __EMPLOYE_CTL_H__
#define __EMPLOYE_CTL_H__
#include "../base.h"

class employe_ctl {
public:
    employe_ctl(std::string path);
private:
    std::vector<employe_t> arr;
};

#endif
