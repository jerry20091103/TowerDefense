#include <functional>
#include <string>
#include <random>

#include "StartScene.hpp"
#include "GameEngine.hpp"
#include "Image.hpp"
#include "Label.hpp"
#include "ImageButton.hpp"
#include "Point.hpp"
#include "AudioHelper.hpp"
#include "StageSelectScene.hpp"
#include "Group.hpp"
#include "Turret.hpp"
#include "MachineGunTurret.hpp"
#include "LightningTurret.hpp"
#include "MissileTurret.hpp"
#include "LaserTurret.hpp"
#include "LaserTurret.hpp"
#include "MissileTurret.hpp"
#include "PlaneEnemy.hpp"
#include "SoldierEnemy.hpp"
#include "TankEnemy.hpp"
#include "BigTankEnemy.hpp"

void StartScene::Initialize()
{
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	// background image
	AddNewObject(new Engine::Image("play/GridLight.png", 0, 0, 1600, 833, 0, 0));
	// topic label
	AddNewObject(new Engine::Label("Tower Defense", "Inkfree.ttf", 80, halfW, halfH / 4 + 10, 0, 0, 0, 255, 0.5, 0.5));
	// start button
	Engine::ImageButton* btn;
	Engine::Label* btntext;
	btn = new Engine::ImageButton("ButtonOut.png", "ButtonIn.png", halfW - 200, halfH / 2 + 450, 400, 100);
	btn->SetOnClickCallback(std::bind(&StartScene::OnClick, this, 1));
	AddNewControlObject(btn);
	AddNewObject(btntext = new Engine::Label("Start", "Inkfree.ttf", 56, halfW, halfH / 2 + 500, 0, 0, 0, 255, 0.5, 0.5));
	btn->SetLabelBinding(btntext);
	// BGM
	bgmInstance = AudioHelper::PlaySample("hotel.ogg", true, AudioHelper::BGMVolume, 0);
	// ground effect
	AddNewObject(GroundEffectGroup = new Group);
	// Turrets
	AddNewObject(TowerGroup = new Group());
	TowerGroup->AddNewObject(new MachineGunTurret(5 * blocksize, 8 * blocksize));
	TowerGroup->AddNewObject(new LightningTurret(10 * blocksize, 8 * blocksize));
	TowerGroup->AddNewObject(new MissileTurret(15 * blocksize, 8 * blocksize));
	TowerGroup->AddNewObject(new LaserTurret(20 * blocksize, 8 * blocksize));
	// Enemies
	AddNewObject(EnemyGroup = new Group());
	// bullets
	AddNewObject(BulletGroup = new Group());
	// effect
	AddNewObject(EffectGroup = new Group());
}

void StartScene::Update(float deltatime)
{
	IScene::Update(deltatime);
	last_spawn += deltatime;
	if (last_spawn > 2.3)
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(1, 4);
		int cur_enemy = dist(rng);
		Enemy* enemy;
		switch (cur_enemy) {
		case 1:
			EnemyGroup->AddNewObject(enemy = new SoldierEnemy(0*blocksize, 6.25 * blocksize));
			break;
		case 2:
			EnemyGroup->AddNewObject(enemy = new PlaneEnemy(0*blocksize, 6.25 * blocksize));
			break;
		case 3:
			EnemyGroup->AddNewObject(enemy = new TankEnemy(0*blocksize, 6.25 * blocksize));
			break;
		case 4:
			EnemyGroup->AddNewObject(enemy = new BigTankEnemy(0 * blocksize, 6.25 * blocksize));
			break;
		default:
			return;
		}
		last_spawn = 0;
		std::vector<std::vector<int>> mapDistance; // dummy
		enemy->UpdatePath(mapDistance);
	}
}

void StartScene::Terminate()
{
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}

void StartScene::OnClick(int stage)
{
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}


