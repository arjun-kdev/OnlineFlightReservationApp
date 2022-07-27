#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct user_login_credentials
{
	char name[32];
	char mobilenumber[16];
	char password[32];
}user_t;

typedef struct date_t
{
	int day;
	int month;
	int year;
}Date;

typedef struct time_t
{
	int hour;
	int minutes;
}Time;


typedef struct tickeT_t
{
	char ticketID[16];
	char flightID[16];
	char serviceNumber[16];
	char source[16];
	char destination[16];
	char passengerID[5][16];
	char gender[5];
	char passengerName[5][32];
	int passengerCount;
	int seatNO[5];
	char doj[16];
	char status[16];
}ticket;


typedef struct flighT_t
{
	char flightName[32];
	char flightID[32];
	char serviceNumber[32];
	char source[64];
	char destination[64];
	char doj[16];
	int number_of_seats[64];
	int total_seats;
	int seats_available;
	char departure_time[16];
	char arrival_time[16];
	double ticket_price;
	char status[16];
	double collected_price;
}flight;

void admin_app();