#include <allegro5/base.h>
#include <string>

#include "AudioHelper.hpp"
#include "LightningBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "StartScene.hpp"
#include "Point.hpp"
#include "LightningTurret.hpp"

const int LightningTurret::Price = 400;
LightningTurret::LightningTurret(float x, float y):
	// TODO 2 (2/8): You can imitate the 2 files: 'MachineGunTurret.hpp', 'MachineGunTurret.cpp' to create a new turret.
	Turret("play/tower-base.png", "play/turret-8.png", x, y, 130, Price, 5.5) 
{
}

void LightningTurret::CreateBullet()
{
	Engine::Point zero(0, 0);
	if (getPlayScene() != nullptr)
		getPlayScene()->BulletGroup->AddNewObject(new LightningBullet(Position, zero, 0, this));
	else if(getStartScene() != nullptr)
		getStartScene()->BulletGroup->AddNewObject(new LightningBullet(Position, zero, 0, this));
	AudioHelper::PlayAudio("lightning.ogg");
}

// overide the Update function to add tint effect
void LightningTurret::Update(float deltatime)
{
	Turret::Update(deltatime);
	int current_tint = 255 - (reload / coolDown) * 200;
	Tint = al_map_rgb(255, 255, current_tint);
}
