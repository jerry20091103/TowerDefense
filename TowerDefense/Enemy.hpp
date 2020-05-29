#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <vector>
#include <string>

#include "Point.hpp"
#include "Sprite.hpp"
#include "PlayScene.hpp"

class Bullet;
class PlayScene;
class StartScene;
class Turret;

class Enemy : public Engine::Sprite {
	friend bool PlayScene::CheckSpaceValid(int, int);
protected:
 	std::vector<Engine::Point> path;
	float speed;
	float hp;
	int money;
	int type; // store which type the enemy is
	PlayScene* getPlayScene();
	StartScene* getStartScene();
	virtual void OnExplode();
public:
	float reachEndTime;
	std::list<Turret*> lockedTurrets;
	std::list<Bullet*> lockedBullets;
	Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money, int type);
 	void Hit(float damage);
	virtual void UpdatePath(const std::vector<std::vector<int>>& mapDistance);
	void Update(float deltaTime) override;
	void Draw() const override;
};
#endif // ENEMY_HPP
