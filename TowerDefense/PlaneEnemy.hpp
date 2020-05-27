#ifndef PLANEENEMY_HPP
#define PLANEENEMY_HPP
#include "Enemy.hpp"

class PlaneEnemy : public Enemy {
public:
	PlaneEnemy(int x, int y);
	void UpdatePath(const std::vector<std::vector<int>>& mapDistance) override;
	void Hit(float damage) override;
};
#endif // PLANEENEMY_HPP
