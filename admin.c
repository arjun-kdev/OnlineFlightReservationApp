//#pragma once
#include "header.h"
#include "flight_db.h"
#include "ticket_db.h"
#include "myutil.h"

void add_flight();
void update_flight_time();
void delete_flight();
void view_all_flight_details();
void update_flight_status();
void view_flight_byServiceNumber();
void view_seats_in_flight();
void view_tickets_flight();
void admin_view_ticket();

void admin_app()
{
	printf("\t***************** Welcome to Admin Terminal *********************\n\n");
	int option;
	
	while(1)
	{
		printf("\n\nSelect Option..\n");
		printf("\t1. Enter new Flight details\n");
		printf("\t2. Update Flight details(time)\n");
		printf("\t3. Delete the Flight\n");
		printf("\t4. View all flights\n");
		printf("\t5. Update Flight status\n");
		printf("\t6. View Flight details(by Service Number)\n");
		printf("\t7. Show seats in Flight\n");
		printf("\t8. View tickets Flight\n");
		printf("\t9. View ticket\n");
		printf("\t0. Exit\n");
	
		printf("\nPlease give the option : ");
		scanf("%d",&option);
	
		switch(option)
		{
			case 1:
					system("clear");
					add_flight();
					break;
		    case 2: 
		    		system("clear");
		    		update_flight_time();
		    		break;
		    case 3:
		    		system("clear");
		    		delete_flight();
		    		break;
		    case 4: 
		    		system("clear");
		    		view_all_flight_details();
		            break;
		    case 5:
		    		system("clear");
		    		update_flight_status();
		    		break;
		    case 6:
		    		system("clear");
		    		view_flight_byServiceNumber();
		    		break;
		    case 7:
		    		system("clear");
		    		view_seats_in_flight();
		    		break;
		    case 8:
		    		system("clear");
		    		view_tickets_flight();
		    		break;
		    case 9:
		    		system("clear");
		    		admin_view_ticket();
		    		break;
		    case 0:
		    		return;
		    default:
		    		printf("You have selected wrong option....\n");		
		}	
  	}
 }
 
 
 void add_flight()
 {
 	flight ft = {};
	Date dt;
	Time t;
	 	
 	printf("\t********** Flight Details ***********\n\n");
 	
 	printf("Flight Name : ");
 	scanf("%s",ft.flightName);
	printf("Flight ID : ");
	scanf("%s",ft.flightID);
	printf("Flight Service Number : ");
	scanf("%s",ft.serviceNumber);
	printf("Starting From : ");
	scanf("%s",ft.source);
	printf("Destination : ");
	scanf("%s",ft.destination);
	clear_input_buffer();
	
	printf("Total seats in Flight : ");
	scanf("%d",&ft.total_seats);
	printf("Date of Journey(D M Y) : ");
	scanf("%d %d %d", &dt.day, &dt.month, &dt.year);
	sprintf(ft.doj,"%02d-%02d-%04d",dt.day,dt.month,dt.year);
	memset(ft.number_of_seats, 0, 64);
	//memset(ZEROARRAY, 0, 1024)
	
	for(int i = 0; i<ft.total_seats; i++)
	{
	  ft.number_of_seats[i] = i+1;
	}
	
	
	ft.seats_available = ft.total_seats;
	
	printf("Departure time(Hr Mi) : ");
	scanf("%d %d", &t.hour, &t.minutes);
	sprintf(ft.departure_time,"%02d : %02d",t.hour,t.minutes);
	printf("Arrival time(Hr Mi) : ");
	scanf("%d %d", &t.hour, &t.minutes);
	sprintf(ft.arrival_time,"%02d : %02d",t.hour,t.minutes);
	
	printf("Ticket Price : ");
	scanf("%lf",&ft.ticket_price);
	ft.collected_price = 0;
	
	printf("Status (Availale / Cancel) : ");
	scanf("%s",ft.status);
	
	
	flight_bdb_insert(&ft);
    system("clear");
}

void view_all_flight_details()
{
	int count = 0;
	
	flight_bdb_read_count(&count);
	
	if(count)
	{
		flight* ft = (flight*)malloc( count * sizeof(flight));
	
		flight_bdb_readAll(ft);
	
		printf("S.No   Flight Name\tFlight ID\t S.Number\tFROM   \t      TO\t    DOJ\t      No.of.Seats    D.Time\tA.Time\t Ticket-Price\t  Status\n\n\n");
	
		for(int i = 0; i < count ; i++)
		{
			printf(" %d      %7s         %7s          ", i+1, ft[i].flightName, ft[i].flightID);
			printf("%6s      %s    %s    ", ft[i].serviceNumber, ft[i].source, ft[i].destination);
			printf("%s         %d        %s    %s    ", ft[i].doj, ft[i].seats_available, ft[i].departure_time, ft[i].arrival_time);	
			printf(" %.2lf       %s\n", ft[i].ticket_price, ft[i].status);
		}
		printf("\n\n");
	}
}																				    
	
void view_flight_byServiceNumber()
{
	flight ft;
	char sNumber[32];
	int count = 0;
	
	printf("Enter Flight service Number you want to search : ");
	scanf("%s",sNumber);
	
	flight_bdb_readByServiceId(&ft,sNumber,&count);
	
	if(count)
	{
		printf("Flight Name : %s\n",ft.flightName);
        printf("Flight ID : %s\n",ft.flightID);
		printf("Flight Service Number : %s\n",ft.serviceNumber);
		printf("Starting From : %s\n",ft.source);
		printf("Destination : %s\n",ft.destination);
		printf("Date of Journey(D M Y) : %s\n",ft.doj);
		printf("Seats Available : %d\n",ft.seats_available);
		printf("Departure time : %s\n",ft.departure_time);
		printf("Arrival time : %s\n",ft.arrival_time);	
		printf("Ticket Price : %.2lf\n",ft.ticket_price);
		printf("Status : %s\n",ft.status);
	}
	else
	{
		printf("\n Flight is not found..\n");
    }		
		
}

void update_flight_time()
{
	flight ft;
	char sNumber[16];
	Time t;
	int count = 0;
	
	printf("Enter flight service Number to update timings : ");
	scanf("%s",sNumber);
	
	flight_bdb_readByServiceId(&ft,sNumber,&count);
	
	if(count)
	{
		printf("Flight Name : %s\n",ft.flightName);
		printf("Flight ID : %s\n",ft.flightID);
		printf("Flight Service Number : %s\n",ft.serviceNumber);
		printf("Starting From : %s\n",ft.source);
		printf("Destination : %s\n",ft.destination);
		printf("Date of Journey(D M Y) : %s\n",ft.doj);
		printf("Seats Available : %d\n",ft.seats_available);
		printf("Departure time : %s\n",ft.departure_time);
		printf("Arrival time : %s\n",ft.arrival_time);	
		printf("Ticket Price : %.2lf\n",ft.ticket_price);
		printf("Status : %s\n",ft.status);
	}
	else
	{
		printf("\n Flight is not found..\n");
		return;
	}
	clear_input_buffer();
	printf("Enter the updated timings : \n Departure Time (Hr Mi) : ");
	scanf("%d %d", &t.hour, &t.minutes);
	sprintf(ft.departure_time,"%02d : %02d",t.hour,t.minutes);
	printf(" Arrival Time (Hr Mi) : ");
	scanf("%d %d", &t.hour, &t.minutes);
	sprintf(ft.arrival_time,"%02d : %02d",t.hour,t.minutes);
	
	flight_bdb_update_time_status(ft);

}
		
void update_flight_status()
{
	flight ft;
	char sNumber[16];
	int count = 0;
	
	printf("Cancelled flight Sevice Number : ");
	scanf("%s",sNumber);
	
	flight_bdb_readByServiceId(&ft,sNumber,&count);
	
	if(count)
	{
		printf("Flight Name : %s\n",ft.flightName);
		printf("Flight ID : %s\n",ft.flightID);
		printf("Flight Service Number : %s\n",ft.serviceNumber);
		printf("Starting From : %s\n",ft.source);
		printf("Destination : %s\n",ft.destination);
		printf("Date of Journey(D M Y) : %s\n",ft.doj);
		printf("Seats Available : %d\n",ft.seats_available);
		printf("Departure time : %s\n",ft.departure_time);
		printf("Arrival time : %s\n",ft.arrival_time);	
		printf("Ticket Price : %.2lf\n",ft.ticket_price);
		printf("Status : %s\n",ft.status);
	}
	else
	{
		printf("\n Flight is not found..\n");
		return;
	}
	
	printf("\n\nPlease Enter the Flight Status : ");
	scanf("%s",ft.status);
	
	flight_bdb_update_time_status(ft);
	
}	
	
void delete_flight()
{	
	flight ft;
	char sNumber[16];
	int count;
	
	printf(" flight Sevice Number to delete : ");
	scanf("%s",sNumber);
	
	flight_bdb_readByServiceId(&ft,sNumber,&count);
	
	if(count)
	{
		printf("Flight Name : %s\n",ft.flightName);
		printf("Flight ID : %s\n",ft.flightID);
		printf("Flight Service Number : %s\n",ft.serviceNumber);
		printf("Starting From : %s\n",ft.source);
		printf("Destination : %s\n",ft.destination);
		printf("Date of Journey(D M Y) : %s\n",ft.doj);
		printf("Seats Available : %d\n",ft.seats_available);
		printf("Departure time : %s\n",ft.departure_time);
		printf("Arrival time : %s\n",ft.arrival_time);	
		printf("Ticket Price : %.2lf\n",ft.ticket_price);
		printf("Status : %s\n",ft.status);
	}
	else
	{
		printf("\n Flight is not found..\n");
		return;
	}
	flight_bdb_delete(sNumber);
}


void view_seats_in_flight()
{
	flight ft;
	char sNumber[16];
	int count;
	
	printf("\nEnter Flight Service Number to see seating : ");
	scanf("%s",sNumber);
	
	flight_bdb_readByServiceId(&ft,sNumber,&count);
	
	if(count)
	{
		for( int i = 0; i < ft.total_seats; i++)
		{
			if(i % 4)
			{
				printf("%4d ",ft.number_of_seats[i]);
			}
			else
			{
				printf("\n%4d ",ft.number_of_seats[i]);
			}
		
		}
	
	}
	else
	{
		printf("\n Flight is not found....\n");
	}

}


void view_tickets_flight()
{
	int count = 0;
	char sNumber[16];
	char doj[16];
	
	printf("Enter Service Number : ");
	scanf("%s", sNumber);
	printf("Enter Date of journey(D-M-Y) : ");
	scanf("%s", doj);
	ticket_bdb_read_ticketcount_serviceNumber_date(&count, sNumber, doj);
	
	if(count)
	{
		ticket *t = (ticket *)malloc(count * sizeof(ticket));
		
		ticket_bdb_readAll_serviceID_date(t, sNumber, doj);
		
		for(int i = 0; i < count; i++)
		{
			printf("\nTicketID : %s\t FlightID : %s\t ServiceID : %s\n", t[i].ticketID, t[i].flightID, t[i].serviceNumber);
			printf("Date of Journey : %s\n", t[i].doj);
			printf("%s - %s\n\n", t[i].source, t[i].destination);
			
		    for(int j = 0; j < t[i].passengerCount; j++)
		    {
		    	printf("%d  %s  %s  %c  %d\n", j+1, t[i].passengerID[j], t[i].passengerName[j], t[i].gender[j], t[i].seatNO[j]);
		    } 
			
    	    printf("status : %s\n", t[i].status);	
		}
	}
	else
	{
		printf("No tickets are booked for this flight....\n");
	}
}


void admin_view_ticket()
{
	char ticket_ID[32];
	ticket t;
	int count = 0;
	
	printf("Enter TicketID : ");
	scanf("%s",ticket_ID);
	
	ticket_bdb_readByTicketId(&t, ticket_ID, &count);
	
	if(count)
	{
		printf("\nTicketID : %s\t FlightID : %s\t ServiceID : %s\n", t.ticketID, t.flightID, t.serviceNumber);
		printf("Date of Journey : %s\n", t.doj);
		printf("%s - %s\n\n", t.source, t.destination);
		
	    for(int i = 0; i < t.passengerCount; i++)
	    {
	    	printf("%d  %s  %s  %c  %d\n", i+1, t.passengerID[i], t.passengerName[i], t.gender[i], t.seatNO[i]);
	    } 
		
        printf("status : %s\n", t.status);
	}
	else
	{
		printf("You have given wrong TicketID....\n");
	}

}




