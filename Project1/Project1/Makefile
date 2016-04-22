CC = g++
OPTIONS = -std=c++11 -lpthread -g -pthread
OBJ = PracticalSocket.o ServerManager.o Client.o Account.o Command.o entry.o SocketAdapter.o HaxorSocket.o Player.o Game.o Lobby.o \
      Card.o Deck.o

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

Command.o: Command.cpp Command.h
	$(CC) $(OPTIONS) -c Command.cpp

Lobby.o: Lobby.cpp Lobby.h
	$(CC) $(OPTIONS) -c Lobby.cpp

Game.o: Game.cpp Game.h
	$(CC) $(OPTIONS) -c Game.cpp

Player.o: Player.cpp Player.h
	$(CC) $(OPTIONS) -c Player.cpp

Card.o: Card.cpp Card.h
	$(CC) $(OPTIONS) -c Card.cpp


entry.o: entry.cpp
	$(CC) $(OPTIONS) -c entry.cpp



.cpp.o:
	$(CC) $(OPTIONS) -c $<
