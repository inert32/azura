#ifndef __SECURE_H__
#define __SECURE_H__

#include "base.h"

extern db_id_t uid;

// 0 - deny, 1 - with limits, 2 - allow
extern char access_list[9];

#endif /* __SECURE_H__ */
