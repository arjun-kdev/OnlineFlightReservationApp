#include"header.h"

typedef struct l_flight
{
	flight ft;
	struct l_flight *next;
}LF;

typedef struct l_ticket
{
	ticket t;
	struct l_ticket *next;
}LT;