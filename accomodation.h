void enter_name();
void find_name();
void find_room();
void checkout_guest();
void view_bookings();

//Instance Field Declaration
FILE* view;
FILE *fp;
FILE* enter;
char admin_entry[20] = {'y'};
char user_entry[20] = {'y'};


struct hotel
{
    char name[20];
    char room[20];
    
}h;