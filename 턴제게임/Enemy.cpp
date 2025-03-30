#include "Enemy.h"
#include <cstdlib>
#include <iostream>

Enemy::Enemy(string name, int health, int defense)
    : Player(name, health, defense) {
}

void Enemy::refillDeck() {
    deck.clear();
    deck.push_back(MonsterCard("적 공격 카드", 25, 0));
    deck.push_back(MonsterCard("적 방어 카드", 0, 12));
    deck.push_back(MonsterCard("적 회복 카드", 0, 0, 10));
    deck.push_back(MonsterCard("적 버프 카드", 5, 5));
    deck.push_back(MonsterCard("적 화상 카드", 10, 0, 0, 0, BURN));
    deck.push_back(MonsterCard("적 빙결 카드", 0, 0, 0, 0, FREEZE));
    deck.push_back(MonsterCard("적 중독 카드", 6, 0, 0, 0, POISON));
    deck.push_back(MonsterCard("적 증폭 카드", 0, 0, 0, 0, AMPLIFY));
    cout << "\n" << name << "의 덱이 새롭게 채워졌습니다.\n";
}

vector<MonsterCard> Enemy::drawMultipleCards(int count)
{
    if (deck.size() < count)
    {
        refillDeck();
    }
    vector<MonsterCard> drawmCards;
    for (int i = 0; i < count && !deck.empty(); ++i)
    {
        int index = rand() % deck.size();
        drawmCards.push_back(deck[index]);
        deck.erase(deck.begin() + index);
    }
    return drawmCards;
}

void Enemy::applyStatusEffect(StatusEffect newEffect, int turns)
{
    status = newEffect;
    statusTurns = turns;
    if (status == AMPLIFY)
    {
        amplifyActive = true;
    }
    cout << name << "에게 상태 이상" << status << "가" << turns << "턴 동안 적용되었습니다.\n";
}

void Enemy::processStatusEffect()
{
    if (status == NONE || statusTurns <= 0)
    {
        return;
    }
    
    switch (status)
    {
    case POISON:
    case BURN:
        health -= 5;
        cout << name << "는 상태 이상으로 5의 피해를 입었습니다.\n";
        break;
    case FREEZE:
        cout << name << "는 빙결 상태로 행동에 제약을 받습니다.\n";
        break;
    case AMPLIFY:
        cout << name << "는 증폭 상태로 다음 공격력이 증가합니다.\n";
    default:
        break;
    }

    statusTurns--;
    if (statusTurns == 0)
    {
        if (status == AMPLIFY)
        {
            amplifyActive = false;
            status = NONE;
            cout << name << "의 상태 이상이 해제되었습니다.\n";
        }   
    }
}