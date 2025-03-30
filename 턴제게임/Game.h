#pragma once
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"

class Game
{
public:
	Player player;
	Enemy enemy;

	int stageNumber;
	bool bossRevived;

	Game();
	void initializeStage();
	void frstmain();
	void start();
	void playTurn();

	vector<PlayerCard> playerSelectCards(vector<PlayerCard>& cards, int count);
	vector<MonsterCard> getRandomCards(vector<MonsterCard>& cards, int count);
	void printCards(const vector<Card>& cards);
	void printCards(const vector<PlayerCard>& cards);
	void printCards(const vector<MonsterCard>& cards);
};
#endif //GAME_H