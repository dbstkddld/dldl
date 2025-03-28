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
			addCard(Card("공격 카드", 10, 0));
			addCard(Card("방어 카드", 0, 10));
			addCard(Card("특수 카드", 5, 5, 5));
			addCard(Card("강화공격 카드", 15, 0));
			addCard(Card("체력회복 카드", 0, 0, 15));
			addCard(Card("방어회복 카드", 0, 10, 0));
			cout << "\n" << name << "의 덱이 새롭게 채워졌습니다.\n";
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
			cout << "\n" << name << "의 체력이 " << amount << "만큼 회복되었습니다.\n";

		}

		void Player::increaseDefense(int amount)
		{
			defense += amount;
			cout << "\n" << name << "의 방어력이 " << amount << "만큼 증가했습니다.\n";

		}



