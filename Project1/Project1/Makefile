CC = g++
OPTIONS = -std=c++11 -lpthread -g -pthread
OBJ = PracticalSocket.o ServerManager.o Client.o Account.o Command.o entry.o SocketAdapter.o HaxorSocket.o

server : $(OBJ)
	$(CC) $(OPTIONS) -o server $(OBJ)

clean :
	- rm -f $(OBJ)
kill :
	- rm -f $(OBJ) server

ServerManager.o: ServerManager.cpp Client.h
	$(CC) $(OPTIONS) -c ServerManager.cpp

PracticalSocket.o: PracticalSocket.cpp
	$(CC) $(OPTIONS) -c PracticalSocket.cpp

Client.o: Client.cpp ServerManager.h
	$(CC) $(OPTIONS) -c Client.cpp

Command.o: Command.cpp
	$(CC) $(OPTIONS) -c Command.cpp

entry.o: entry.cpp
	$(CC) $(OPTIONS) -c entry.cpp


.c.o:
	$(CC) $(OPTIONS) -c $<
