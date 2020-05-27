#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <string>
#include <vector>

#include "Enemy.hpp"
#include "GameEngine.hpp"
#include "LOG.hpp"
#include "PlayScene.hpp"
#include "PlaneEnemy.hpp"
#include "AudioHelper.hpp"
#include "Turret.hpp"
#include "bullet.hpp"

PlaneEnemy::PlaneEnemy(int x, int y) : Enemy("play/enemy-2.png", x, y, 16, 120, 10, 10) {
	// Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
	// and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}

// overide the UpdatePath function to change enemyplane's behavior
void PlaneEnemy::UpdatePath(const std::vector<std::vector<int>>& mapDistance)
{
	path = std::vector<Engine::Point>(1);
	path[0] = PlayScene::EndGridPoint;
}

void PlaneEnemy::Hit(float damage)
{
	hp -= damage;
	if (hp <= 0) {
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it : lockedTurrets)
			it->Target = nullptr;
		for (auto& it : lockedBullets)
			it->Target = nullptr;
		getPlayScene()->EarnMoney(money);
		getPlayScene()->PlaneEnemyGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}
