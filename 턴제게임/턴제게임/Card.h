#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

using namespace std;

class Card
{
public:
	string name;
	int attack;
	int defense;
	int heal;
	int defenseHeal;

	Card(string name, int attack = 0, int defense = 0, int heal = 0, int defenseHeal = 0);

};
#endif //"Card.h"