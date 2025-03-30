#include "Game.h"
#include "Enemy.h"

#include <ctime>
#include <cstdlib>


	Game::Game() : player("플레이어", 300, 10), enemy("적", 30, 0), stageNumber(1), bossRevived(false)
	{
		srand(static_cast<unsigned int>(time(0)));
		frstmain();
		initializeStage();
	
	}
	void Game::initializeStage()
	{
		cout << "\n=====스테이지" << stageNumber << "시작=====\n";
		bossRevived = false;
		if (stageNumber % 5 == 0)
		{
			cout << "보스 몬스터 등장!";
			enemy = Enemy("보스 몬스터", 100 + 30 * stageNumber, 10 + 20 * stageNumber);
		}
		else
		{
			enemy = Enemy("적", 30 + 10 * stageNumber, 5 + stageNumber);
		}

		player.refillDeck();
		enemy.refillDeck();
	}
	void Game::frstmain()
	{
		int a;
		cout << "게임을 시작할려면 1번, 종료는 0번\n";
		cin >> a;
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (a == 0)
		{
			cout << "게임이 종료되었습니다.\n";
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
			cout << "게임 시작\n";


			while (player.health > 0 && enemy.health > 0)
			{
				playTurn();
				player.turnCount++;
				player.canRedraw = true;
				player.health += player.regenAmount;

				if (enemy.health <= 0 && stageNumber % 5 == 0 && !bossRevived)
				{
					cout << "보스 몬스터가 부활합니다!\n";

					enemy.health = (100 + 30 * stageNumber) / 2;
					bossRevived = true;
				}
			}

			if (player.health <= 0)
			{
				cout << "플레이어 패배\n";
				break;
			}
			else
			{
				cout << stageNumber << "스테이지 클리어\n";
				stageNumber++;
			}
		}
		frstmain();
	}

	void Game::playTurn()
	{
		player.processStatusEffect();

		if (player.status == FREEZE) {
			cout << "플레이어가 빙결 상태이므로 턴을 스킵합니다.\n";
			return;
		}
		//system("cls");
		
		enemy.processStatusEffect();

		cout << "\n====================================\n";
		cout << "=== 턴 시작 ===\n";
		cout << "플레이어 체력 : " << player.health << " | 적 체력 : " << enemy.health << endl;
		cout << "플레이어 방어력 : " << player.defense << " | 적 방어력 : " << enemy.defense << endl;
		cout << "====================================\n";
		
		int playerDrawCount = (player.status == FREEZE) ? 1 : 5 + player.turnCount / 5;
		int enemyDrawCount = (enemy.status == FREEZE) ? 1 : 5;

		vector<PlayerCard> availableCards = player.drawMultipleCards(playerDrawCount);

		cout << "\n현재 드로우된 카드:\n";
		printCards(availableCards);

		if (availableCards.empty()) {
			cout << "드로우할 카드가 없습니다! 턴을 스킵합니다.\n";
			player.turnCount++;
			player.canRedraw = true;
			player.health += player.regenAmount;

			return printCards(availableCards);
		}

		if (player.canRedraw && playerDrawCount > 1)
		{
			int redrawChoice;
			cout << "\n카드를 다시 뽑으시겠습니다?\n (1 = 예, 0 = 아니요) : ";
			cin >> redrawChoice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (redrawChoice == 1)
			{
				availableCards = player.drawMultipleCards(playerDrawCount);
				player.canRedraw = false;
				cout << "카드를 다시 뽑았습니다.\n";
				cout << "\n새로 드로우된 카드:\n";
				printCards(availableCards);
			}
		}
		
		vector<PlayerCard> selectedCards = playerSelectCards(availableCards, min(3, playerDrawCount));
		
		vector<MonsterCard> enemyCards = enemy.drawMultipleCards(enemyDrawCount);
		vector<MonsterCard> enemySelected = getRandomCards(enemyCards, min(3, enemyDrawCount));

		cout << "\n플레이어가 선택한 카드 :\n";
		printCards(selectedCards);
		cout << "\n적이 선택한 카드:\n";
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
			cout << "\n플레이어는 증폭 상태로 공격력이 증가합니다.\n";
		}
		if (enemy.amplifyActive)
		{
			totalEnemyAttack = static_cast<int>(totalEnemyAttack * 1.5);
			cout << "\n적은 증폭 상태로 공격력이 증가합니다.\n";
		}

		cout << "\n플레이어의 총 공격력: " << totalPlayerAttack << endl;
		cout << "\n적의 총 공격력: " << totalEnemyAttack << endl;

		int playerDamage = max(0, totalPlayerAttack - totalEnemyDefense);
		int enemyDamage = max(0, totalEnemyAttack - totalPlayerDefense);

		player.health -= enemyDamage;
		enemy.health -= playerDamage;

		cout << "\n플레이어는 " << enemyDamage << "의 피해를 입음!\n";
		cout << "\n적은 " << playerDamage << "의 피해를 입음!\n";

		player.processStatusEffect();
		if (player.health <= 0) return;
	}

	void Game::printCards(const vector<Card>& cards)
	{
		for (const auto& card : cards)
		{
			cout << "[" << card.name << "] 공격력: " << card.attack << " 방어력: " << card.defense
				<< " 회복: " << card.heal << " 방어 회복: " << card.defenseHeal << "\n";
		}
	}

	vector<PlayerCard> Game::playerSelectCards(vector<PlayerCard>& cards, int count)
	{
		vector<PlayerCard> selected;
		while (selected.size() < count)
		{
			cout << "\n--------------------------------------------------------------\n";
			cout << "사용할 카드 선택 (" << selected.size() + 1 << "/" << count << "):\n";
			for (int i = 0; i < cards.size(); i++)
			{
				cout << i + 1 << ". [" << cards[i].name << "] 공격력: " << cards[i].attack
					<< " 방어력: " << cards[i].defense << " 회복: " << cards[i].heal
					<< " 방어 회복: " << cards[i].defenseHeal << "\n";
			}

			int choice;
			cout << "\n번호 입력: ";
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (choice >= 1 && choice <= cards.size())
			{
				selected.push_back(cards[choice - 1]);
				cards.erase(cards.begin() + (choice - 1));
			}
			else
			{
				cout << "잘못된 입력입니다. 다시 선택하세요.\n";
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
			cout << "[" << card.name << "] 공격력: " << card.attack
				<< " 방어력: " << card.defense << " 회복: " << card.heal
				<< " 방어 회복: " << card.defenseHeal << "\n";
		}
	}

	void Game::printCards(const vector<MonsterCard>& cards)
	{
		for (const auto& card : cards)
		{
			cout << "[" << card.name << "] 공격력: " << card.attack
				<< " 방어력: " << card.defense << " 회복: " << card.heal
				<< " 방어 회복: " << card.defenseHeal << "\n";
		}
	}
	

	