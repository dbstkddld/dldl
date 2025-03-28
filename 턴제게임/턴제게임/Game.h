#pragma once
#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game
{
public:
	Player player;
	Player enemy;

	Game();
	void initializeDecks();
	void frstmain();
	void start();
	void playTurn();
	vector<Card> playerSelectCards(vector<Card>& cards, int count);
	vector<Card> getRandomCards(vector<Card>& cards, int count);
	void printCards(const vector<Card>& cards);
};
#endif //GAME_H