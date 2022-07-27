#pragma once
#include "header.h"

void ticket_bdb_insert(ticket* );
void ticket_bdb_read_count(int* );
void ticket_bdb_readAll(ticket* );
void ticket_bdb_readByTicketId(ticket* , char* , int* );
void ticket_bdb_read_ticketcount_serviceNumber_date(int* , char* , char* );
void ticket_bdb_readAll_serviceID_date(ticket* , char* , char* );
void ticket_bdb_update_status(ticket );
