#include "Lobby.h"



Lobby::Lobby()
{
	games.push_back(new Game());
}


Lobby::~Lobby()
{
	for (gameIterator = games.begin(); gameIterator != games.end(); ) {
		delete *gameIterator;
	}
}
std::string Lobby::GetGameList() {
	std::string gameList;
	for (gameIterator = games.begin(); gameIterator != games.end(); gameIterator++) {
		gameList += (*gameIterator)->GetName();
		gameList += " ";
	}
	return gameList;
}
std::string Lobby::GetNumGames() {
	std::string numString;
	numString = games.size();
	return numString;
}

std::string Lobby::GetPlayers() {
	std::string playerList;
	for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++) {
		playerList += (*playerIterator)->GetName();
	}
}
std::string Lobby::GetNumPlayers() {
	std::string numString;
	numString = players.size();
	return numString;
}
void Lobby::MakeGame(std::string name){
}
