#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
//#include "wkq.cpp"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

class Player
{
public:
	string name;
	int health;
	int defense;
	int amount;
	vector<PlayerCard> deck;
	int turnCount;
	bool canRedraw;
	StatusEffect status;
	int statusTurns;
	int regenAmount;
	int cardsUsed;
	bool amplifyActive;

	Player(string name, int health, int defense);

	void addCard(const PlayerCard& card);
	void refillDeck();
	vector<PlayerCard> drawMultipleCards(int count);
	void heal(int amount);
	void increaseDefense(int amount);
	void applyStatusEffect(StatusEffect newEffect, int turns);
	void processStatusEffect();
};
#endif // PLAYER_H