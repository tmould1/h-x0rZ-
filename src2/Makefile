CC = g++
OPTIONS = -std=c++11 -lpthread -g -pthread
OBJ = PracticalSocket.o entry.o Client.o

server : $(OBJ)
	$(CC) $(OPTIONS) -o server $(OBJ)

clean :
	- rm -f $(OBJ)
kill :
	- rm -f $(OBJ) server

PracticalSocket.o: PracticalSocket.cpp
	$(CC) $(OPTIONS) -c PracticalSocket.cpp

Client.o: Client.cpp
	$(CC) $(OPTIONS) -c Client.cpp

entry.o: entry.cpp
	$(CC) $(OPTIONS) -c entry.cpp


.c.o:
	$(CC) $(OPTIONS) -c $<
