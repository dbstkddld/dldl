#include "Game.h"

#include <ctime>
#include <cstdlib>


	Game::Game() : player("�÷��̾�", 30, 10), enemy("��", 30, 0)
	{
		srand(time(0));
		initializeDecks();
	
	}
	void Game::initializeDecks()
	{
		player.refillDeck();
		enemy.refillDeck();

	}
	void Game::frstmain()
	{
		int a;
		cout << "������ �����ҷ��� 1��, ����� 0��";
		cin >> a;

		if (a == 0)
		{
			return;
		}
		else if (a == 1)
		{
			Game::start();
		}
	}
	void Game::start()
	{
		cout << "���� ����\n";
		while (player.health > 0 && enemy.health > 0)
		{
			playTurn();
		}

		if (player.health <= 0)
		{
			cout << "�÷��̾� �й�\n";
		}
		else
		{
			cout << "�÷��̾� �¸�\n";
		}
	};

	void Game::playTurn()
	{
		system("cls");
		cout << "\n====================================\n";
		cout << "=== �� ���� ===\n";
		cout << "�÷��̾� ü�� : " << player.health << " | �� ü�� : " << enemy.health << endl;
		cout << "�÷��̾� ���� : " << player.defense << " | �� ���� : " << enemy.defense << endl;
		cout << "====================================\n";
		
		vector<Card> availableCards = player.drawMultipleCards(5);
		vector<Card> selectedCards = playerSelectCards(availableCards, 3);
		
		vector<Card> enemyCards = enemy.drawMultipleCards(5);
		vector<Card> enemySelected = getRandomCards(enemyCards, 3);

		cout << "\n�÷��̾ ������ ī�� :\n";
		printCards(selectedCards);
		cout << "\n���� ������ ī��:\n";
		printCards(enemySelected);

		int totalPlayerAttack = 0, totalPlayerDefense = 0;
		int totalEnemyAttack = 0, totalEnemyDefense = 0;

		for (auto& card : selectedCards)
		{
			totalPlayerAttack += card.attack;
			totalPlayerDefense += card.defense;

			if (card.heal > 0)
			{
				player.heal(card.heal);
			}
			if (card.defenseHeal > 0)
			{
				player.increaseDefense(card.defenseHeal);
			}
		}

		for (auto& card : enemySelected)
		{
			totalEnemyAttack += card.attack;
			totalEnemyDefense += card.defense;

			if (card.heal > 0)
			{
				enemy.heal(card.heal);
			}
			if (card.defenseHeal > 0)
			{
				enemy.increaseDefense(card.defenseHeal);
			}
		}

		cout << "\n�÷��̾��� �� ���ݷ�: " << totalPlayerAttack << endl;
		cout << "\n���� �� ���ݷ�: " << totalEnemyAttack << endl;

		int playerDamage = max(0, totalPlayerAttack - totalEnemyDefense);
		int enemyDamage = max(0, totalEnemyAttack - totalPlayerDefense);

		player.health -= enemyDamage;
		enemy.health -= playerDamage;

		cout << "\n�÷��̾�� " << enemyDamage << "�� ���ظ� ����!\n";
		cout << "\n���� " << playerDamage << "�� ���ظ� ����!\n";
	}


	vector<Card> Game::playerSelectCards(vector<Card>& cards, int count)
	{
		vector<Card> selected;
		while (selected.size() < count)
		{
			cout << "\n--------------------------------------------------------------";
			cout << "\n����� ī�� ���� (" << selected.size() + 1 << "/" << count << "):\n";
			for (int i = 0; i < cards.size(); i++)
			{
				cout << i + 1 << ". [" << cards[i].name << "] ���ݷ�: " << cards[i].attack
					<< " ����: " << cards[i].defense << " ȸ��: " << cards[i].heal
					<< " ��� ȸ��: " << cards[i].defenseHeal << "\n";
			}

			int choice;
			cout << "\n��ȣ �Է�: ";
			cin >> choice;

			if (choice >= 1 && choice <= cards.size())
			{
				selected.push_back(cards[choice - 1]);
				cards.erase(cards.begin() + (choice - 1));
			}
			else
			{
				cout << "�߸��� �Է��Դϴ�. �ٽ� �����ϼ���.\n";
			}
		}
		return selected;
	}

	vector<Card> Game::getRandomCards(vector<Card>& cards, int count)
	{
		vector<Card> selected;
		vector<int> usedIndexes;

		while (selected.size() < count)
		{
			int index = rand() % cards.size();
			if (find(usedIndexes.begin(), usedIndexes.end(), index) == usedIndexes.end())
			{
				selected.push_back(cards[index]);
				usedIndexes.push_back(index);
			}
		}

		return selected;
	}

	void Game::printCards(const vector<Card>& cards)
	{
		for (const auto& card : cards)
		{
			cout << "[" << card.name << "] ���ݷ�: " << card.attack << " ����: " << card.defense
				<< " ȸ��: " << card.heal << " ��� ȸ��: " << card.defenseHeal << "\n";
		}
	}
