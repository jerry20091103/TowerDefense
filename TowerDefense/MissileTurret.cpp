#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "MissileBullet.hpp"
#include "MissileTurret.hpp"
#include "PlayScene.hpp"
#include "StartScene.hpp"
#include "Point.hpp"

const int MissileTurret::Price = 300;
MissileTurret::MissileTurret(float x, float y) :
	Turret("play/tower-base.png", "play/turret-3.png", x, y, 600, Price, 4) {
}
void MissileTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
	// Change bullet position to the front of the gun barrel.
	if (getPlayScene() != nullptr)
	{
		getPlayScene()->BulletGroup->AddNewObject(new MissileBullet(Position + normalized * 10 - normal * 6, diff, rotation, this));
		getPlayScene()->BulletGroup->AddNewObject(new MissileBullet(Position + normalized * 10 + normal * 6, diff, rotation, this));
	}
	else if (getStartScene() != nullptr)
	{
		getStartScene()->BulletGroup->AddNewObject(new MissileBullet(Position + normalized * 10 - normal * 6, diff, rotation, this));
		getStartScene()->BulletGroup->AddNewObject(new MissileBullet(Position + normalized * 10 + normal * 6, diff, rotation, this));
	}
	AudioHelper::PlayAudio("missile.wav");
}
