#pragma once
#include"header.h"
void flight_bdb_insert(flight* );
void flight_bdb_read_count(int* );
void flight_bdb_readAll(flight* );
void flight_bdb_readByServiceId(flight* , char*, int* );
void flight_bdb_update_time_status(flight );
void flight_bdb_delete(char* );
void flight_bdb_read_count_seat(int* , int *);


void flight_bdb_readBy_src_dest_date_count(int* , char* , char* , char* );
void flight_bdb_readBy_src_dest_date(flight* , char* , char* , char*);
void flight_bdb_readByServiceId_date(flight* , char* , char* , int* );
