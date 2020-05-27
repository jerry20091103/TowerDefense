#include <random>
#include <string>

#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "LightningBullet.hpp"
#include "Collider.hpp"

LightningBullet::LightningBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret * parent):
	Bullet("play/lightning260r.png", 0, 3, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent)
{
	CollisionRadius = 130;
}

void LightningBullet::OnExplode(Enemy * enemy)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
}

// overide the Update function since the behavor of the bullet is different
void LightningBullet::Update(float deltaTime)
{
	static float LastShootTimeStamp = 0;
	LastShootTimeStamp += deltaTime;
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	// Can be improved by Spatial Hash, Quad Tree, ...
	// However simply loop through all enemies is enough for this program.
	// add PlaneEnemyGroup !
	for (auto& it : scene->EnemyGroup->GetObjects()) {
		Enemy* enemy = dynamic_cast<Enemy*>(it);
		if (!enemy->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
			OnExplode(enemy);
			enemy->Hit(damage);
		}
	}
	for (auto& it : scene->PlaneEnemyGroup->GetObjects()) {
		Enemy* enemy = dynamic_cast<Enemy*>(it);
		if (!enemy->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
			OnExplode(enemy);
			enemy->Hit(damage);
		}
	}
	if (LastShootTimeStamp >= 0.15)
	{
		LastShootTimeStamp = 0;
		getPlayScene()->BulletGroup->RemoveObject(objectIterator);
	}
	// Check if out of boundary.
	//if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), PlayScene::GetClientSize()))
	//	getPlayScene()->BulletGroup->RemoveObject(objectIterator);
}
