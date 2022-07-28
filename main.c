//#pragma once
#include"header.h"

/*typedef struct user_login_credentials
{
	char name[32];
	char mobilenumber[16];
	char password[32];
}user_t;
*/

/*void user_app()
{
}
void admin_app()
{
}*/

void user_app();

void user_signup();
void user_login();
void change_password();
void user_bdb_readByMobileNumber(user_t* , char* );
void user_bdb_update_password(user_t );
void admin_login();
int check_admin_login(char* , char* );
int check_user_login(user_t );
void user_bdb_readByUsername(user_t* , char* );
void user_bdb_insert(user_t* );



int main()
{
	
	char option = ' ', retry = ' ';
	int count = 0;
	
    printf("\n\n\t*********** Welcome to Flight Booking System **************\n\n");
    
    do{
    	printf("\t1. User Signup\n\t2. User login\n\t3. Admin login\n\t0. Exit\n\n");
    	char option;
    	printf("Enter the option : ");
    	scanf("%c",&option);
    
    	switch(option)
    	{
    		case '1':
    					system("clear");
    					user_signup();
    					user_login();
    					break;
    		case '2':
    					system("clear");
    					user_login();
    					break;
    		case '3':
    					system("clear");
    					admin_login();
    					break;
        	case '0':	
        				return 0;
        	default:
        				printf("Entered Invalid Option....\n");
        				printf("Do you want to try again(Y/N) ?");
        				scanf(" %c",&retry);
        				count++;			
        				break;
        }	
					
	}while( (retry == 'Y' || retry == 'y') && (count < 3));

    printf("\n\n**************** Thank You *******************\n\n");

}

void user_signup()
{
	
	user_t user;
	
	printf("Please provide user name : ");
	scanf("%s",user.name);
	printf("Please provide mobile number : ");
	scanf("%s",user.mobilenumber);
	printf("Please enter password for further login : ");
	scanf("%s",user.password);
	
	
	user_bdb_insert(&user);
	printf("Thank you for signing up\n");
	printf("Now you are able to book the tickets\n\n");
	
}

void user_login()
{

	user_t user1;
	int count = 0;
	char ch;
	
	while(count < 3)
	{
		printf("Enter user name : ");
		scanf("%s",user1.name);
		printf("Enter user password : ");
		scanf("%s",user1.password);
	
		if(check_user_login(user1))
		{
			system("clear");
			user_app();
			count = 4;
			break;
		}
		else
		{
			printf("Invalid user name/password\n");
			printf("Please try again...\n\n");
		    count++;
		    system("clear");
		} 
	}
	
	if(count == 3)
	{
		printf("You have entered Invalid Credentials for multiple times\n");
		printf("We are Unable to proceed you\n\n");
		printf("Do you want to change the password (Y/N) : ");
		scanf(" %c",&ch);
		
		if( ch == 'Y')
		{
			system("clear");
			change_password();
		}		
	}
	else
	{
		printf("Thank You for using our services\n\n");
	}	   
}


void admin_login()
{
    char admin_username[32];
    char admin_password[32];
    int count = 0;
    
    while(count < 3)
    {
	    printf("Enter admin name : ");
    	scanf("%s", admin_username);
    
    	printf("Enter admin password : ");
    	scanf("%s", admin_password);
    
    	if(check_admin_login(admin_username, admin_password))
    	{
    		system("clear");
    		admin_app();
    		break;
    	}
    	else
    	{
    	 	printf("Invalid admin Name/Password\n");
    	 	printf("Please try again\n\n");
    	 	count++;
    	 	system("clear");
    	}
    }
    
    if(count == 3)
	{
		printf("You have entered Invalid Credentials for multiple times\n");
		printf("We are Unable to proceed you\n\n");
		printf("Please restart the application...\n");
	}     	 		
}

int check_admin_login(char* name, char* password)
{
    char user_names[4][32] = {"Arjun", "Pooja", "Suma", "Syram"};
    char user_passwords[4][32] = {"1234", "1234", "1234", "1234"};
    
    for(int index = 0; index < 4; index++)
    {
    	if((strcmp(user_names[index],name) == 0) && (strcmp(user_passwords[index],password) == 0))
    	{
    		return 1;
    	}
    }
    return 0;	
}


int check_user_login(user_t user1)
{
 	user_t user;
 	user_bdb_readByUsername(&user, user1.name);
 	
 	if(!(strcmp(user.name,user1.name)) && !(strcmp(user.password, user1.password)))
 	{
 		return 1;
 	}
 	else
 	{
 		return 0;
 	}
}



void user_bdb_readByUsername(user_t* user, char* name){
  
    int I=0;
    user_t user1;
    
    char fileName[] = "user.dat";
    FILE* in = fopen(fileName,"rb");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&user1,1,sizeof(user_t),in)){
        if(!strcmp(user1.name,name)){
        	(*user) = user1;
        	break;
        }
        I++;
    }
    fclose(in);
    
}

void user_bdb_insert(user_t* user)
{
    char fileName[] = "user.dat";
    FILE* out = fopen(fileName,"ab");
    if(out == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    fwrite(user,1,sizeof(user_t),out);
    fclose(out);
}

void change_password()
{
	char mNumber[16], otp[16];
	int i = 0;
	user_t user;
	printf("\nPlease enter the registered mobile number : ");
	scanf("%s",mNumber);
	user_bdb_readByMobileNumber(&user, mNumber);
	
	if(!(strcmp(user.mobilenumber, mNumber)))
	{
		printf("Please Enter the OTP received in your mobile : ");
		scanf("%6s",otp);
		for(i = 0; i < 6; i++)
		{
		  if( otp[i] < '0' || otp[i] > '9' )
		  {
		  	printf("Invalid otp...\n");
		  	break;
		  	return;
		  }
		}
		
		if( i == 6 )
		{
			printf("\nEnter the new password : ");
			scanf("%s",user.password);
			user_bdb_update_password(user);
			printf("Your password is Updated....\n\n");
		}
	}
	else
	{
		printf("\nEntered mobile number is wrong....\n");
	}	
}

void user_bdb_update_password(user_t user){
	int I=0;
 	user_t user1;
    
    char fileName[] = "user.dat";
    FILE* in = fopen(fileName,"rb+");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&user1,1,sizeof(user_t),in)){
    	I++;
    	if(!(strcmp(user1.mobilenumber, user.mobilenumber))){        	
        	break;
        }        
    }
    if(I > 0){
    	fseek(in,(I-1)*sizeof(user_t),SEEK_SET);
    	fwrite(&user,1,sizeof(user_t),in);
    }
    fclose(in);
}


void user_bdb_readByMobileNumber(user_t* user, char* mNumber){
  
    int I=0;
    user_t user1;
    
    char fileName[] = "user.dat";
    FILE* in = fopen(fileName,"rb");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&user1,1,sizeof(user_t),in)){
        if(!strcmp(user1.mobilenumber,mNumber)){
        	(*user) = user1;
        	break;
        }
        I++;
    }
    fclose(in);   
}



