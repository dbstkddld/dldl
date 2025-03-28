#include "Game.h"

#include <ctime>
#include <cstdlib>


	Game::Game() : player("플레이어", 30, 10), enemy("적", 30, 0)
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
		cout << "게임을 시작할려면 1번, 종료는 0번";
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
		cout << "게임 시작\n";
		while (player.health > 0 && enemy.health > 0)
		{
			playTurn();
		}

		if (player.health <= 0)
		{
			cout << "플레이어 패배\n";
		}
		else
		{
			cout << "플레이어 승리\n";
		}
	};

	void Game::playTurn()
	{
		system("cls");
		cout << "\n====================================\n";
		cout << "=== 턴 시작 ===\n";
		cout << "플레이어 체력 : " << player.health << " | 적 체력 : " << enemy.health << endl;
		cout << "플레이어 방어력 : " << player.defense << " | 적 방어력 : " << enemy.defense << endl;
		cout << "====================================\n";
		
		vector<Card> availableCards = player.drawMultipleCards(5);
		vector<Card> selectedCards = playerSelectCards(availableCards, 3);
		
		vector<Card> enemyCards = enemy.drawMultipleCards(5);
		vector<Card> enemySelected = getRandomCards(enemyCards, 3);

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

		cout << "\n플레이어의 총 공격력: " << totalPlayerAttack << endl;
		cout << "\n적의 총 공격력: " << totalEnemyAttack << endl;

		int playerDamage = max(0, totalPlayerAttack - totalEnemyDefense);
		int enemyDamage = max(0, totalEnemyAttack - totalPlayerDefense);

		player.health -= enemyDamage;
		enemy.health -= playerDamage;

		cout << "\n플레이어는 " << enemyDamage << "의 피해를 입음!\n";
		cout << "\n적은 " << playerDamage << "의 피해를 입음!\n";
	}


	vector<Card> Game::playerSelectCards(vector<Card>& cards, int count)
	{
		vector<Card> selected;
		while (selected.size() < count)
		{
			cout << "\n--------------------------------------------------------------";
			cout << "\n사용할 카드 선택 (" << selected.size() + 1 << "/" << count << "):\n";
			for (int i = 0; i < cards.size(); i++)
			{
				cout << i + 1 << ". [" << cards[i].name << "] 공격력: " << cards[i].attack
					<< " 방어력: " << cards[i].defense << " 회복: " << cards[i].heal
					<< " 방어 회복: " << cards[i].defenseHeal << "\n";
			}

			int choice;
			cout << "\n번호 입력: ";
			cin >> choice;

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
			cout << "[" << card.name << "] 공격력: " << card.attack << " 방어력: " << card.defense
				<< " 회복: " << card.heal << " 방어 회복: " << card.defenseHeal << "\n";
		}
	}
