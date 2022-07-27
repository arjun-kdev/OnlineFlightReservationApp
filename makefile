CC=gcc
SRC=main.c myutil.c user.c admin.c flight_db.c ticket_db.c -lpthread
EXE=flight
build:
	$(CC) -g $(SRC) -o $(EXE)
run:
	./$(EXE)
clean:
	rm -f *.o *.s *.i $(EXE)
lint:
	splint $(SRC)
check:
	valgrind --leak-check=yes ./$(EXE)
execute: clean build run
memcheck: clean build check