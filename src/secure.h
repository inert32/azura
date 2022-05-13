#ifndef __SECURE_H__
#define __SECURE_H__

#include "base.h"

extern db_id_t uid;

std::string rid_to_text(const roles role);
roles int_to_rid(const int role);
int rid_to_int(const roles role);

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
