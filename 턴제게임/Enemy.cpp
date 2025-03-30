#include "Enemy.h"
#include <cstdlib>
#include <iostream>

Enemy::Enemy(string name, int health, int defense)
    : Player(name, health, defense) {
}

void Enemy::refillDeck() {
    deck.clear();
    deck.push_back(MonsterCard("�� ���� ī��", 25, 0));
    deck.push_back(MonsterCard("�� ��� ī��", 0, 12));
    deck.push_back(MonsterCard("�� ȸ�� ī��", 0, 0, 10));
    deck.push_back(MonsterCard("�� ���� ī��", 5, 5));
    deck.push_back(MonsterCard("�� ȭ�� ī��", 10, 0, 0, 0, BURN));
    deck.push_back(MonsterCard("�� ���� ī��", 0, 0, 0, 0, FREEZE));
    deck.push_back(MonsterCard("�� �ߵ� ī��", 6, 0, 0, 0, POISON));
    deck.push_back(MonsterCard("�� ���� ī��", 0, 0, 0, 0, AMPLIFY));
    cout << "\n" << name << "�� ���� ���Ӱ� ä�������ϴ�.\n";
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
    cout << name << "���� ���� �̻�" << status << "��" << turns << "�� ���� ����Ǿ����ϴ�.\n";
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
        cout << name << "�� ���� �̻����� 5�� ���ظ� �Ծ����ϴ�.\n";
        break;
    case FREEZE:
        cout << name << "�� ���� ���·� �ൿ�� ������ �޽��ϴ�.\n";
        break;
    case AMPLIFY:
        cout << name << "�� ���� ���·� ���� ���ݷ��� �����մϴ�.\n";
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
            cout << name << "�� ���� �̻��� �����Ǿ����ϴ�.\n";
        }   
    }
}