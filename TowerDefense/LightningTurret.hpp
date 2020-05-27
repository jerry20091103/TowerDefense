#ifndef LIGHTNINGTURRET_HPP
#define LIGHTNINGTURRET_HPP
#include "Turret.hpp"

class LightningTurret : public Turret {
public:
	static const int Price;
	LightningTurret(float x, float y);
	void CreateBullet() override;
	void Update(float deltatime) override;
};
#endif // LIGHTNINGTURRET_HPP
