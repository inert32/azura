#ifndef __TOUR_CTL_H__
#define __TOUR_CTL_H__

#include <string>
#include <vector>
#include <filesystem>
#include "../base.h"

class tour_ctl {
public:
    tour_ctl(std::filesystem::path file_path);
private:
    std::vector<tour_t> arr;
};

#endif
