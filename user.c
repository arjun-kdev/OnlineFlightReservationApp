#include "header.h"
#include "flight_db.h"
#include "ticket_db.h"
#include "myutil.h"
#include "user.h"
#include "accomodation.h"

void book_tickets();
void view_ticket();
void cancel_tickets();
void Accomodation();

void user_app()
{
	int option;
	printf("\t**************** Welcome ***************\n\n");
	while(1)
	{		
		printf("Select the option....\n");
		printf("\t1. Book Tickets\n");
		printf("\t2. View Tickets\n");
		printf("\t3. Cancel Tickets\n");
		printf("\t4. View Accomodation\n");
		printf("\t0. Exit\n\n");
		printf("Please select the option : ");
    	scanf("%d",&option);
    
    	switch(option)
    	{
    		case 1:
    				system("clear");
    				book_tickets();
    				break;
    		case 2:
    				system("clear");
    				view_ticket();
    				break;
    	    case 3:
    	    		system("clear");
    	    		cancel_tickets();
    	    		break;
    	    case 4:
    	    		system("clear");
    	    		Accomodation();
    	    		break;
    	    case 0:
    	    		return;
    	    default:
    	    		printf("\n Invalid option selected ...");
    	    		break;
    	}
    }
}


void book_tickets()
{
	char src[32];
	char dest[32];
	Date dt;
	char doj[16];
	char sNumber[16];
	int count = 0, index = 0;
    flight *ft;
    flight FT;
	
	printf("Enter the From : ");
	scanf("%s",src);
	printf("Enter the To : ");
	scanf("%s",dest);
	clear_input_buffer();
	
	printf("Enter the date of Journey(D M Y) : ");
	scanf("%d %d %d", &dt.day, &dt.month, &dt.year);
	sprintf(doj,"%02d-%02d-%02d", dt.day, dt.month, dt.year);
	
	flight_bdb_readBy_src_dest_date_count(&count, src, dest, doj);
	
	if(count)
	{
		ft = (flight *)malloc(count * sizeof(flight));
		flight_bdb_readBy_src_dest_date(ft, src, dest, doj);
		
		printf("S.No   Flight Name\tFlight ID\t S.Number\tFROM   \t      TO\t    DOJ\t      No.of.Seats    D.Time\tA.Time\t Ticket-Price\t  Status\n\n\n");
	
		for(int i = 0; i < count ; i++)
		{
			printf(" %d      %7s         %7s          ", i+1, ft[i].flightName, ft[i].flightID);
			printf("%6s      %s    %s    ", ft[i].serviceNumber, ft[i].source, ft[i].destination);
			printf("%s         %d        %s    %s    ", ft[i].doj, ft[i].seats_available, ft[i].departure_time, ft[i].arrival_time);	
			printf(" %.2lf       %s\n", ft[i].ticket_price, ft[i].status);
		}
		printf("\n\n");
		
		printf("Please Enter Service Number of Flight to view the seats : ");
		scanf("%s", sNumber);	
		
		for(index = 0; index < count; index++)
		{
		   if( !strcmp(ft[index].serviceNumber, sNumber))
		   {
		   		FT = ft[index];
		   		break;
		   }
		}
		
		if(index == count)
		{
			printf("\n You have given wrong service number....\n");
			return;
		}
		
		
		for( int i = 0; i < FT.total_seats; i++)
		{
			if(i % 4)
			{
				printf("%4d ",FT.number_of_seats[i]);
			}
			else
			{
				printf("\n%4d ",FT.number_of_seats[i]);
			}
        }
        printf("\n");
        
        ticket t;
        
        printf("How many tickets you want to book : ");
        scanf("%d",&t.passengerCount);
        
        if( t.passengerCount > FT.seats_available )
        {
        	printf(" only %d seats are avaiable\n",FT.seats_available);
        	return;
        }
        
        for(int i = 0; i < t.passengerCount ; i++)
        {
         	printf("Enter passenger %d details...", i+1);
         	printf("\tEnter Passenger Name : ");
         	scanf("%s",t.passengerName[i]);
         	printf("\tEnter Passenger Id : ");
         	scanf("%s",t.passengerID[i]);
         	printf("\tEnter gender : ");
         	scanf(" %c",&t.gender[i]);
         	printf("Enter seat number that is available : ");
         	scanf("%d",&t.seatNO[i]);
         	
         	int j = 0;
         	for(j = 0; j < FT.total_seats; j++)
         	{
         	  if(FT.number_of_seats[j] == t.seatNO[i])
         	  		break;
         	}
         	if( j == FT.total_seats )
         	{
         		printf("\n%d is already booked\n",t.seatNO[i]);
         		printf("Enter passenger details again with proper seat number\n");
         		i--;
         	}
        }
        
        strcpy(t.flightID, FT.flightID);
        strcpy(t.serviceNumber, FT.serviceNumber);
        strcpy(t.doj, FT.doj);
        strcpy(t.source, FT.source);
        strcpy(t.destination, FT.destination);
        
        count = 0;
        ticket_bdb_read_ticketcount_serviceNumber_date(&count, t.serviceNumber, t.doj);
        
        FT.collected_price = FT.collected_price + t.passengerCount * FT.ticket_price;
        
        sprintf(t.ticketID,"%s%s%d", FT.doj, FT.serviceNumber, ++count);
        printf("\nYour TicketID : %s\n",t.ticketID);
        
        strcpy(t.status, "accept");
        
        ticket_bdb_insert(&t); 
        
        for(int i = 0; i < t.passengerCount; i++)
        {
        	for( int j = 0; j < FT.total_seats; j++)
        	{
        		if(FT.number_of_seats[j] == t.seatNO[i])
        		{
        			FT.number_of_seats[j] = 0;
        			break;
        		}
        	}
        }
        
        FT.seats_available = FT.seats_available - t.passengerCount;
        flight_bdb_update_time_status(FT); 
              
	}
	else
	{
		printf("\n No Flights are available for your request...\n\n");
	}
	system("clear");
}


void view_ticket()
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


void cancel_tickets()
{
	char ticket_ID[32];
	int count = 0, option;
	ticket t;
	flight ft;
	
	printf("Enter ticket ID : ");
	scanf("%s",ticket_ID);
	clear_input_buffer();
	
	ticket_bdb_readByTicketId(&t, ticket_ID, &count);
	
	if(count)
	{
		
		    flight_bdb_readByServiceId_date(&ft, t.serviceNumber, t.doj, &count);
	
			for(int i = 0; i < t.passengerCount; i++)
			{
				int seat = t.seatNO[i];
				ft.number_of_seats[seat - 1] = t.seatNO[i];
			}
			sprintf(t.status,"cancelled");
			ft.collected_price = ft.collected_price - ft.ticket_price * t.passengerCount;
			
			ticket_bdb_update_status(t);
			flight_bdb_update_time_status(ft);
		
	}
	else
	{
		printf("\nTicket is not available.....\n");
	}

}

//main method
void Accomodation(){ 

    int a,b,c;

     //Welcome screen

 	printf("\n\n\t\t*************************************************\n");
	printf("\t\t*      WELCOME TO ACCOMODATION FACILITY         *\n");
	printf("\t\t*************************************************\n\n\n");

       printf("\n\tFor ADMIN access enter --> 1 \t\t\t");
       printf("\n\tFor USER access enter --> 2 \t\t\t");
       printf("\n>> ");
     scanf("%d",&a);

        switch(a){
            case 1:{
                char pass[10];
                char filepass[10];
                int i;

                FILE *passw;
                passw = fopen("pass.txt","r");

                //admins password prompt
                printf("\n Hello admin!\n Please enter the password to continue --> ");

                for(i=0; i<6; i++){
                    scanf("%s",pass);
                    fscanf(passw,"%s",filepass);
                    if (strcmp(filepass,pass) == 0) {
                        printf("\n\nAccess granted!\n");
                        fclose(passw);
                        break;
                    }
                    else{
                     printf("\nIncorrect password, please try again.");
                     printf("\nYou have %d trys left ",5-i-1);
                     printf("\n\nEnter password >> ");
                    }
                    if(i==4){
                        fclose(passw);
                        return 0;
                    }

               
                }

                 //re-entry if
                while(admin_entry[0] =='y'){

                printf("\n>>>>>>>>>>>>\tTo VIEW booking requests --> 1 \t\t\t<<<<<<<<<<<<");
                 printf("\n>>>>>>>>>>>>\tTo VIEW booked guests details --> 2 \t\t\t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo ENTER new guest --> 3 \t\t\t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo CHECKOUT room number of existing guest --> 4 <<<<<<<<<<<<\n");
                printf(">> ");
                scanf("%d",&b);

                switch(b){
                    case 1:{
                        view_bookings();
                        break;
                    }
                        case 2:{
                        FILE* fpi;
                        fpi = fopen("hotelnew.txt","r");	

                        while(fscanf(fpi,"%s %s ",h.name,h.room) != -1){	
                         
                          printf("%s %s  \n",h.name,h.room);
                         }
                         break;
                    }
                    case 3:{
                        enter_name();
                        break;
                    }
                   
                case 4:{
                    checkout_guest();
                    break;
                    }
                    default:{
                        printf("\n Wrong entry!");
                    }
                }
                //enter again?
                printf("Would you like to continue? (y/n)\n");
                scanf("%s",admin_entry);

                }
                if(strcmp(admin_entry,"n") == 0){
                    printf("Exiting...\n");
                    printf("\e[1;1H\e[2J");
                    printf("\n >Exited<\n\n");
                    //system("clear");
                    return 0;
                }
                else{
                    printf("Wrong entry!\nExiting...\n");
                    return 0;
                }
                break;
            }
            
                     
            case 2:{
                while(user_entry[0] =='y'){
                printf("\nHello user and welcome to Hotel!");
                printf("\n\tTo view available rooms --> 1 \t\t\t");
                // printf("\n\tEnter number of room to be book --> 2 \t\t\t");
   	            printf("\n\tTo request booking of room --> 3 \t");
                printf("\n>> ");
                scanf("%d",&c);
                switch(c){
                    case 1:{
                        FILE* view;
                        view = fopen("rooms.txt","r");
                        printf("Available rooms are:");
                        while(fscanf(view,"%s",h.room) != -1){	
                        printf("%s ",h.room);
                        }
                        fclose(view);
                        break;
                    }
                     //case 2:{
                        
                        //printf("Enter number of room to  be book: ");
                        //scanf("%s",h.room);
                        

                      // break;
                   // }

                    case 3:{
                        printf("Enter your name: ");
                       scanf("%s",h.name);
                        printf("Enter room to book: ");
                        scanf("%s",h.room);
                        

                        enter = fopen("bookings.txt","a");

                        fprintf(enter,"%s %s ",h.name,h.room);
                        fprintf(enter,"\n");

                        printf("Succesfully requested booking\n");
                        fclose(enter);

                    }
                }
                    
                printf("\nWould you like to continue? (y/n)\n");
                scanf("%s",user_entry);

                }
                if(strcmp(user_entry,"n") == 0){
                    printf("Exiting...\n");
                    printf("\e[1;1H\e[2J");
                    printf("\n >Exited<\n\n");
                    //system("clear");
                    return 0;
                }
                else{
                    printf("Wrong entry!\nExiting...\n");
                    return 0;
                }
                break;
            }
        }
}

//method declare to enter name
void enter_name(){ 

    FILE *tmp1; 
    FILE *tmp2;

    printf("\nEnter guest name --> ");
    scanf("%s",h.name);
    printf("\nEnter their room number --> ");
    scanf("%s",h.room);
    
    
    //entering guests
    fp = fopen("hotelnew.txt","a");

    if( fp == NULL){
        printf("\nFile not found");
        exit(1);
    }
    else{
        fprintf(fp,"%s %s",h.name,h.room);
        printf("\nDone\n");
    }
    fprintf(fp,"\n");

    //
    char remove_guest[15];
    strcpy(remove_guest,h.name);
    char remove_room[15];
    strcpy(remove_room,h.room);

    //removing booking
    tmp1 = fopen("tmp1.txt","a");
    enter = fopen("bookings.txt","r");
 
    while(fscanf(enter,"%s %s ",h.name,h.room) != -1){
            fgetc(enter);	
		    
			    if(strcmp(h.name,remove_guest) != 0){
                    fprintf(tmp1,"%s %s ",h.name,h.room);
                }
        }
    fclose(enter);
    fclose(tmp1);
    remove("bookings.txt");
    rename("tmp1.txt","bookings.txt");
    fclose(fp);

    //removing room
    tmp2 = fopen("tmp2.txt","a");
    view = fopen("rooms.txt","r");

    
    while(fscanf(view,"%s",h.room) != -1){
			    if(strcmp(h.room,remove_room) != 0){
                    fprintf(tmp2,"%s",h.room);
                    fprintf(tmp2,"\n");
                }
        }
    fclose(view);
    fclose(tmp2);
    remove("rooms.txt");
    rename("tmp2.txt","rooms.txt");


  //  fclose(fp);
}

//method definition for guest checkout
void checkout_guest(){
    char buffer2[20];
    char checkout_name[20];
    char add_room[20];

    FILE *tmp;

    printf("Enter guest too checkout ");
    scanf("%s",checkout_name);

    fp = fopen("hotelnew.txt","r");
    tmp = fopen("tmp.txt","w");

    if(fp == NULL){
    printf("File not found");
    exit(1);
    }
	else{
        while(fscanf(fp,"%s %s ",h.name,h.room) != -1){
            fgetc(fp);	
		  
			    if(strcmp(h.name,checkout_name) != 0){
                    fprintf(tmp,"%s %s ",h.name,h.room);
                }
                else{
                   strcpy(add_room,h.room);
                }
        }
        printf("Room checked out!");
    }

    fclose(fp);
    fclose(tmp);
    remove("hotelnew.txt");
    rename("tmp.txt","hotelnew.txt");

    //enter room back into available rooms list
    view = fopen("rooms.txt","a");
    printf(" add is %s",add_room);
    fprintf(view,"%s",add_room);
    fclose(view);

}


//method defined to view bookings
void view_bookings(){

    enter = fopen("bookings.txt","r");	

    while(fscanf(enter,"%s %s ",h.name,h.room) != -1){	
        printf("%s %s  \n",h.name,h.room);
  }  
}
