#pragma once
#include <vector>
#include <string>
#include "Game.h"
#include "Player.h"

class Game;
class Player;

class Lobby
{
private:
	std::vector<Game *> games;
	std::vector<Game *>::iterator gameIterator;
	std::vector<Player *> players;
	std::vector<Player *>::iterator playerIterator;
	int maxGames;
	int maxPlayers;
public:
	Lobby();
	~Lobby();
	std::string GetGameList();
	std::string GetNumGames();
	std::string GetPlayers();
	std::string GetNumPlayers();
	void MakeGame(std::string name);

};

