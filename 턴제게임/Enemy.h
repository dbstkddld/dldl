#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include "Card.h"

class Enemy : public Player {
public:
    vector<MonsterCard> deck;
    
    Enemy(string name, int health, int defense);

    void refillDeck();
    vector<MonsterCard> drawMultipleCards(int count);

    void applyStatusEffect(StatusEffect newEffect, int turns);
    void processStatusEffect();
};

#endif //ENEMY_H
