#include "Player.h"

	Player::Player(string name, int health, int defense)
		: name(name), health(health), defense(defense), turnCount(1), amount(0), canRedraw(true), status(NONE), statusTurns(0), regenAmount(2), cardsUsed(0), amplifyActive(false) { }

		void Player::addCard(const PlayerCard& card)
		{
			deck.push_back(card);
		}

		void Player::refillDeck()
		{
			deck.clear();
			addCard(PlayerCard("공격 카드", 30, 0));
			addCard(PlayerCard("방어 카드", 0, 10));
			addCard(PlayerCard("특수 카드", 5, 5, 5));
			addCard(PlayerCard("강화공격 카드", 15, 0));
			addCard(PlayerCard("체력회복 카드", 0, 0, 15));
			addCard(PlayerCard("방어회복 카드", 0, 10, 0));
			addCard(PlayerCard("화상 카드", 8, 0, 0, 0, BURN));
			addCard(PlayerCard("중독 카드", 5, 0, 0, 0, POISON));
			addCard(PlayerCard("빙결 카드", 0, 0, 0, 0, FREEZE));
			addCard(PlayerCard("증폭 카드", 0, 0, 0, 0, AMPLIFY));
			cout << "\n" << name << "의 덱이 새롭게 채워졌습니다.\n";
		}
		vector<PlayerCard> Player::drawMultipleCards(int count)
		{
			//int drawCount = min(5 + turnCount / 2, (int)deck.size());

			if (deck.size() < count)
				refillDeck();

			vector<PlayerCard> drawnCards;
			for (int i = 0; i < count && !deck.empty(); ++i)
			{
				int index = rand() % deck.size();
				drawnCards.push_back(deck[index]);
				deck.erase(deck.begin() + index);
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

		void Player::applyStatusEffect(StatusEffect newEffect, int turns)
		{
			status = newEffect;
			statusTurns = turns;
			if (status == AMPLIFY) amplifyActive = true;
			cout << name << "에게 상태 이상 " << status << "가 " << turns << "턴 동안 적용되었습니다.\n";
		}


		void Player::processStatusEffect()
		{
			if (status == NONE || statusTurns <= 0)
				return;

			switch (status)
			{
			case POISON:
			case BURN:
				health -= 5;
				cout << name << "는 상태 이상으로 5의 피해를 입었습니다!\n";
				break;
			case FREEZE:
				cout << name << "는 빙결 상태로 행동에 제약을 받습니다.\n";
				break;
			case AMPLIFY:
				cout << name << "는 증폭 상태로 공격력이 증가합니다!\n";
				break;
			default:
				break;
			}

			statusTurns--;
			if (statusTurns == 0)
			{
				if (status == AMPLIFY) amplifyActive = false;
				status = NONE;
				cout << name << "의 상태 이상이 해제되었습니다.\n";
			}
		}


