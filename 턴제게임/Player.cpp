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
			addCard(PlayerCard("���� ī��", 30, 0));
			addCard(PlayerCard("��� ī��", 0, 10));
			addCard(PlayerCard("Ư�� ī��", 5, 5, 5));
			addCard(PlayerCard("��ȭ���� ī��", 15, 0));
			addCard(PlayerCard("ü��ȸ�� ī��", 0, 0, 15));
			addCard(PlayerCard("���ȸ�� ī��", 0, 10, 0));
			addCard(PlayerCard("ȭ�� ī��", 8, 0, 0, 0, BURN));
			addCard(PlayerCard("�ߵ� ī��", 5, 0, 0, 0, POISON));
			addCard(PlayerCard("���� ī��", 0, 0, 0, 0, FREEZE));
			addCard(PlayerCard("���� ī��", 0, 0, 0, 0, AMPLIFY));
			cout << "\n" << name << "�� ���� ���Ӱ� ä�������ϴ�.\n";
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
			cout << "\n" << name << "�� ü���� " << amount << "��ŭ ȸ���Ǿ����ϴ�.\n";

		}

		void Player::increaseDefense(int amount)
		{
			defense += amount;
			cout << "\n" << name << "�� ������ " << amount << "��ŭ �����߽��ϴ�.\n";

		}

		void Player::applyStatusEffect(StatusEffect newEffect, int turns)
		{
			status = newEffect;
			statusTurns = turns;
			if (status == AMPLIFY) amplifyActive = true;
			cout << name << "���� ���� �̻� " << status << "�� " << turns << "�� ���� ����Ǿ����ϴ�.\n";
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
				cout << name << "�� ���� �̻����� 5�� ���ظ� �Ծ����ϴ�!\n";
				break;
			case FREEZE:
				cout << name << "�� ���� ���·� �ൿ�� ������ �޽��ϴ�.\n";
				break;
			case AMPLIFY:
				cout << name << "�� ���� ���·� ���ݷ��� �����մϴ�!\n";
				break;
			default:
				break;
			}

			statusTurns--;
			if (statusTurns == 0)
			{
				if (status == AMPLIFY) amplifyActive = false;
				status = NONE;
				cout << name << "�� ���� �̻��� �����Ǿ����ϴ�.\n";
			}
		}


