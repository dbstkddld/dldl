#include "Game.h"
#include "Enemy.h"

#include <ctime>
#include <cstdlib>


	Game::Game() : player("�÷��̾�", 300, 10), enemy("��", 30, 0), stageNumber(1), bossRevived(false)
	{
		srand(static_cast<unsigned int>(time(0)));
		frstmain();
		initializeStage();
	
	}
	void Game::initializeStage()
	{
		cout << "\n=====��������" << stageNumber << "����=====\n";
		bossRevived = false;
		if (stageNumber % 5 == 0)
		{
			cout << "���� ���� ����!";
			enemy = Enemy("���� ����", 100 + 30 * stageNumber, 10 + 20 * stageNumber);
		}
		else
		{
			enemy = Enemy("��", 30 + 10 * stageNumber, 5 + stageNumber);
		}

		player.refillDeck();
		enemy.refillDeck();
	}
	void Game::frstmain()
	{
		int a;
		cout << "������ �����ҷ��� 1��, ����� 0��\n";
		cin >> a;
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (a == 0)
		{
			cout << "������ ����Ǿ����ϴ�.\n";
			exit(0);
		}
		else if (a == 1)
		{
			Game::start();
		}
	}
	void Game::start()
	{
		while (true)
		{
			initializeStage();
			cout << "���� ����\n";


			while (player.health > 0 && enemy.health > 0)
			{
				playTurn();
				player.turnCount++;
				player.canRedraw = true;
				player.health += player.regenAmount;

				if (enemy.health <= 0 && stageNumber % 5 == 0 && !bossRevived)
				{
					cout << "���� ���Ͱ� ��Ȱ�մϴ�!\n";

					enemy.health = (100 + 30 * stageNumber) / 2;
					bossRevived = true;
				}
			}

			if (player.health <= 0)
			{
				cout << "�÷��̾� �й�\n";
				break;
			}
			else
			{
				cout << stageNumber << "�������� Ŭ����\n";
				stageNumber++;
			}
		}
		frstmain();
	}

	void Game::playTurn()
	{
		player.processStatusEffect();

		if (player.status == FREEZE) {
			cout << "�÷��̾ ���� �����̹Ƿ� ���� ��ŵ�մϴ�.\n";
			return;
		}
		//system("cls");
		
		enemy.processStatusEffect();

		cout << "\n====================================\n";
		cout << "=== �� ���� ===\n";
		cout << "�÷��̾� ü�� : " << player.health << " | �� ü�� : " << enemy.health << endl;
		cout << "�÷��̾� ���� : " << player.defense << " | �� ���� : " << enemy.defense << endl;
		cout << "====================================\n";
		
		int playerDrawCount = (player.status == FREEZE) ? 1 : 5 + player.turnCount / 5;
		int enemyDrawCount = (enemy.status == FREEZE) ? 1 : 5;

		vector<PlayerCard> availableCards = player.drawMultipleCards(playerDrawCount);

		cout << "\n���� ��ο�� ī��:\n";
		printCards(availableCards);

		if (availableCards.empty()) {
			cout << "��ο��� ī�尡 �����ϴ�! ���� ��ŵ�մϴ�.\n";
			player.turnCount++;
			player.canRedraw = true;
			player.health += player.regenAmount;

			return printCards(availableCards);
		}

		if (player.canRedraw && playerDrawCount > 1)
		{
			int redrawChoice;
			cout << "\nī�带 �ٽ� �����ðڽ��ϴ�?\n (1 = ��, 0 = �ƴϿ�) : ";
			cin >> redrawChoice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (redrawChoice == 1)
			{
				availableCards = player.drawMultipleCards(playerDrawCount);
				player.canRedraw = false;
				cout << "ī�带 �ٽ� �̾ҽ��ϴ�.\n";
				cout << "\n���� ��ο�� ī��:\n";
				printCards(availableCards);
			}
		}
		
		vector<PlayerCard> selectedCards = playerSelectCards(availableCards, min(3, playerDrawCount));
		
		vector<MonsterCard> enemyCards = enemy.drawMultipleCards(enemyDrawCount);
		vector<MonsterCard> enemySelected = getRandomCards(enemyCards, min(3, enemyDrawCount));

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
			if (card.effect != NONE)
			{
				enemy.applyStatusEffect(card.effect, 3);
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
			if (card.effect != NONE)
			{
				player.applyStatusEffect(card.effect, 3);
			}
		}
		if (player.amplifyActive)
		{
			totalPlayerAttack = static_cast<int>(totalPlayerAttack * 1.5);
			cout << "\n�÷��̾�� ���� ���·� ���ݷ��� �����մϴ�.\n";
		}
		if (enemy.amplifyActive)
		{
			totalEnemyAttack = static_cast<int>(totalEnemyAttack * 1.5);
			cout << "\n���� ���� ���·� ���ݷ��� �����մϴ�.\n";
		}

		cout << "\n�÷��̾��� �� ���ݷ�: " << totalPlayerAttack << endl;
		cout << "\n���� �� ���ݷ�: " << totalEnemyAttack << endl;

		int playerDamage = max(0, totalPlayerAttack - totalEnemyDefense);
		int enemyDamage = max(0, totalEnemyAttack - totalPlayerDefense);

		player.health -= enemyDamage;
		enemy.health -= playerDamage;

		cout << "\n�÷��̾�� " << enemyDamage << "�� ���ظ� ����!\n";
		cout << "\n���� " << playerDamage << "�� ���ظ� ����!\n";

		player.processStatusEffect();
		if (player.health <= 0) return;
	}

	void Game::printCards(const vector<Card>& cards)
	{
		for (const auto& card : cards)
		{
			cout << "[" << card.name << "] ���ݷ�: " << card.attack << " ����: " << card.defense
				<< " ȸ��: " << card.heal << " ��� ȸ��: " << card.defenseHeal << "\n";
		}
	}

	vector<PlayerCard> Game::playerSelectCards(vector<PlayerCard>& cards, int count)
	{
		vector<PlayerCard> selected;
		while (selected.size() < count)
		{
			cout << "\n--------------------------------------------------------------\n";
			cout << "����� ī�� ���� (" << selected.size() + 1 << "/" << count << "):\n";
			for (int i = 0; i < cards.size(); i++)
			{
				cout << i + 1 << ". [" << cards[i].name << "] ���ݷ�: " << cards[i].attack
					<< " ����: " << cards[i].defense << " ȸ��: " << cards[i].heal
					<< " ��� ȸ��: " << cards[i].defenseHeal << "\n";
			}

			int choice;
			cout << "\n��ȣ �Է�: ";
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

	vector<MonsterCard> Game::getRandomCards(vector<MonsterCard>&cards, int count)
	{
		vector<MonsterCard> selected;
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

	void Game::printCards(const vector<PlayerCard>& cards)
	{
		for (const auto& card : cards)
		{
			cout << "[" << card.name << "] ���ݷ�: " << card.attack
				<< " ����: " << card.defense << " ȸ��: " << card.heal
				<< " ��� ȸ��: " << card.defenseHeal << "\n";
		}
	}

	void Game::printCards(const vector<MonsterCard>& cards)
	{
		for (const auto& card : cards)
		{
			cout << "[" << card.name << "] ���ݷ�: " << card.attack
				<< " ����: " << card.defense << " ȸ��: " << card.heal
				<< " ��� ȸ��: " << card.defenseHeal << "\n";
		}
	}
	

	