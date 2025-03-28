#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"

#include <vector>
#include <iostream>

class Player
{
public:
	string name;
	int health;
	int defense;
	int amount;
	vector<Card> deck;

	Player(string name, int health, int defense);

	void addCard(const Card& card);
	void refillDeck();
	vector<Card> drawMultipleCards(int count);
	void heal(int amount);
	void increaseDefense(int amount);

};
#endif // PLAYER_H