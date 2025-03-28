#include "Player.h"
#include "string"
#include <algorithm>
#include <cstdlib>



	Player::Player(string name, int health, int defense) : name(name), health(health), defense(0) {}

		void Player::addCard(const Card& card)
		{
			deck.push_back(card);
		}

		void Player::refillDeck()
		{
			deck.clear();
			addCard(Card("���� ī��", 10, 0));
			addCard(Card("��� ī��", 0, 10));
			addCard(Card("Ư�� ī��", 5, 5, 5));
			addCard(Card("��ȭ���� ī��", 15, 0));
			addCard(Card("ü��ȸ�� ī��", 0, 0, 15));
			addCard(Card("���ȸ�� ī��", 0, 10, 0));
			cout << "\n" << name << "�� ���� ���Ӱ� ä�������ϴ�.\n";
		}
		vector<Card> Player::drawMultipleCards(int count)
		{
			vector<Card> drawnCards;
			vector<int> usedIndexes;

			if (deck.size() < count);
			{
				refillDeck();
			}

			while (drawnCards.size() < count)
			{
				int index = rand() % deck.size();
				if (find(usedIndexes.begin(), usedIndexes.end(), index) == usedIndexes.end())
				{
					drawnCards.push_back(deck[index]);
					usedIndexes.push_back(index);
				}
			}
			return drawnCards;
		}

		void Player::heal(int amount)
		{
			health += amount;
			cout << "\n" << name << "�� ü���� " << amount << "��ŭ ȸ���Ǿ����ϴ�.\n";

		}

		void Player::increaseDefense(int amount)
		{
			defense += amount;
			cout << "\n" << name << "�� ������ " << amount << "��ŭ �����߽��ϴ�.\n";

		}



