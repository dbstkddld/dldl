#include "Player.h"
#include "Enemy.h"

class EnemyAI
{
	public:
		static vector<MonsterCard> selectCards
		(
			const vector<MonsterCard>& hand,
			const Player& player,
			int currentHealth,
			int count
		)
		{
			vector<MonsterCard> sorted = hand;

			sort(sorted.begin(), sorted.end(), [&](count MonsterCard& a, count MonsterCard b)
				{

				}
		}
};