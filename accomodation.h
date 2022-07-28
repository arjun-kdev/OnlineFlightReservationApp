void enter_name();
void find_name();
void find_room();
void checkout_guest();
void view_bookings();

//Instance Field Declaration
FILE* view;
FILE *fp;
FILE* enter;
extern char admin_entry;
extern char user_entry;


struct hotel
{
    char name[20];
    char room[20];
    
}h;