#ifndef __SECURE_H__
#define __SECURE_H__

#include "base.h"

extern db_id_t uid;

// 0 - deny, 1 - with limits, 2 - allow
extern char access_list[9];
/* Roles:
 * |---------------+---------+------------+-------------------+-----------|
 * | Role          | Role ID | tourist_t  | tour_t            | employe_t |
 * |---------------+---------+------------+-------------------+-----------|
 * | Group manager |    0    | if allowed | if id=manager id  |     no    |
 * |               |         | by tour    |                   |           |
 * |---------------+---------+------------+-------------------+-----------|
 * | Seller        |    1    |    RW      |       RO          | to id=0   |
 * |---------------+---------+------------+-------------------+-----------|
 * | Boss          |    2    |    RW      |       RW          |     RW    |
 * |---------------+---------+------------+-------------------+-----------|
*/
#endif /* __SECURE_H__ */
