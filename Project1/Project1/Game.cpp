#include "Game.h"
#include <ctime>
#include <cstdlib>


Game::Game()
{
	srand(time(NULL));
	for (int i = 0; i < 5; i++) {
		actualCards[i] = new Card(1);
	}
	for (int j = 0; j < 2; j++) {
		actualCards[5 + j] = new Card(2);
	}
	for (int k = 0; k < 2; k++) {
		actualCards[7 + k] = new Card(3);
	}
	for (int l = 0; l < 2; l++) {
		actualCards[9 + l] = new Card(4);
	}
	for (int l = 0; l < 2; l++) {
		actualCards[11 + l] = new Card(5);
	}
	actualCards[13] = new Card(6);
	actualCards[14] = new Card(7);
	actualCards[15] = new Card(8);

}


Game::~Game()
{
	for (int i = 0; i < 15; i++) {
		delete actualCards[i];
	}
}

void Game::Shuffle() {
	// Random Number Fun
	int randPos;
	int deckCount = 16;
	std::vector<Card *> shuffleDeck;

	for (int i = 0; i < 16; i++) {
		shuffleDeck.push_back(actualCards[i]);
	}

	for (int i = 0; i < 16; i++) {
		randPos = rand() % deckCount;
		deck.push_back(shuffleDeck.at(randPos));
		shuffleDeck.erase(shuffleDeck.begin() + randPos);
		deckCount--;
	}
}

void Game::StartGame() {
	Shuffle();
	faceDownCard = drawCard();
	if (players.size() == 2) {
		BurnThreeCard();
	}
	ActivePlayerIterator = players.begin();
	DealCard();
	// Pass ball to Client  =?=  send "UpdateGameInfo" Command to all players?
}

void Game::DealCard() {
	(*ActivePlayerIterator)->ReceiveCard(drawCard());
}

void Game::GiveCard(Player * toPlayer) {
	toPlayer->ReceiveCard(drawCard());
}

// drawCard
// @return Card * to the recently removed deck Card
Card* Game::drawCard() {
	Card * tmpCardPtr;
	tmpCardPtr = deck.front();
	deck.erase(deck.begin());
	return tmpCardPtr;
}

void Game::AdvanceActivePlayerMarker() {
	// Advance The Active Player Marker
	std::advance(ActivePlayerIterator, 1);
	if (ActivePlayerIterator == players.end()) {
		ActivePlayerIterator = players.begin();
	}
}

void Game::BurnThreeCard() {
	for (int i = 0; i < 3; i++) {
		burnPile.push_back(drawCard());
	}
}

std::string Game::GetName() {
	return name;
}
