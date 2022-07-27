#include "header.h"
#include "ticket_db.h"


void ticket_bdb_insert(ticket* tkt)
{
    char fileName[] = "Tickets.dat";
    FILE* out = fopen(fileName,"ab");
    if(out == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    fwrite(tkt,1,sizeof(ticket),out);
    fclose(out);
}

void ticket_bdb_read_count(int* countAddr)
{
    int I=0;
    ticket TKT;
    
    char fileName[] = "Tickets.dat";
    FILE* in = fopen(fileName,"rb");
    if(in == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&TKT,1,sizeof(ticket),in))
    {
        I++;
    }
    fclose(in);
    (*countAddr) = I;
}


void ticket_bdb_readAll(ticket* tkt)
{
    int I=0;
    ticket TKT;
    
    char fileName[] = "Tickets.dat";
    FILE* in = fopen(fileName,"rb");
    if(in == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&TKT,1,sizeof(ticket),in))
    {
        tkt[I] = TKT;
        I++;
    }
    fclose(in);
}


void ticket_bdb_readAll_serviceID_date(ticket* tkt, char* sNumber, char* doj)
{
    int I=0;
    ticket TKT;
    
    char fileName[] = "Tickets.dat";
    FILE* in = fopen(fileName,"rb");
    if(in == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&TKT,1,sizeof(ticket),in))
    {
    	if(!strcmp(TKT.serviceNumber, sNumber)  &&  !strcmp(TKT.doj, doj))
    	{
        	tkt[I] = TKT;
        	I++;
        }
    }
    fclose(in);
}



void ticket_bdb_readByTicketId(ticket* tkt, char* sTicket, int* count)
{  
    int I=0;
    ticket TKT;
    
    char fileName[] = "Tickets.dat";
    FILE* in = fopen(fileName,"rb");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&TKT,1,sizeof(ticket),in)){
        if(!strcmp(TKT.ticketID,sTicket)){
        	(*tkt) = TKT;
        	(*count)++;
        	break;
        }
        I++;
    }
    fclose(in);
}


void ticket_bdb_read_ticketcount_serviceNumber_date(int* count, char* sNumber, char* doj)
{  
    ticket TKT;
    
    char fileName[] = "Tickets.dat";
    FILE* in = fopen(fileName,"rb");
    if(in == NULL){
        //printf("FILE ERROR.\n");
        return;
    }
    while(fread(&TKT,1,sizeof(ticket),in)){
        if(!strcmp(TKT.serviceNumber, sNumber)  &&  !strcmp(TKT.doj, doj)){
        	(*count)++;
        }
    }
    fclose(in);
}


void ticket_bdb_update_status(ticket t)
{
	int I=0;
    ticket TKT;
    
    char fileName[] = "Tickets.dat";
    FILE* in = fopen(fileName,"rb+");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&TKT,1,sizeof(ticket),in)){
    	I++;
    	if(!(strcmp(TKT.ticketID, t.ticketID))){        	
        	break;
        }        
    }
    if(I > 0){
    	fseek(in,(I-1)*sizeof(ticket),SEEK_SET);
    	fwrite(&t,1,sizeof(ticket),in);
    }
    fclose(in);
}


