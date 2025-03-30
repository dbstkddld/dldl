#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum StatusEffect {NONE, POISON, BURN, FREEZE, BUFF, DEBUFF, AMPLIFY};

class Card
{
public:
	string name;
	int attack;
	int defense;
	int heal;
	int defenseHeal;
	StatusEffect effect;

	Card(string name, int attack = 0, int defense = 0, int heal = 0, int defenseHeal = 0, StatusEffect effecf = NONE);
	virtual ~Card() = default;
};


class PlayerCard : public Card
{
public:
	PlayerCard(string name = "", int attack = 0, int defense = 0, int heal = 0, int defenseHeal = 0, StatusEffect effect = NONE)
		: Card(name, attack, defense, heal, defenseHeal, effect) {
	}

};

class MonsterCard : public Card
{
public:
	MonsterCard(string name = "", int attack =0, int defense = 0, int heal = 0, int defenseHeal = 0, StatusEffect effect = NONE)
		: Card(name, attack, defense, heal, defenseHeal, effect) {
	}

};

#endif //"Card.h"