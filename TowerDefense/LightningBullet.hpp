#ifndef LIGHTNINGBULLET_HPP
#define LIGHTNINGBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
	struct Point;
}  // namespace Engine

class LightningBullet : public Bullet {
public:
	explicit LightningBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) override;
	void Update(float deltaTime) override;
};
#endif // LIGHTNINGBULLET_HPP
