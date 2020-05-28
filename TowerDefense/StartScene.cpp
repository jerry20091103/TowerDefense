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
	startbtn = new Engine::ImageButton("ButtonOut.png", "ButtonIn.png", halfW - 200, halfH * 8 / 5 - 50, 400, 100);
	startbtn->SetOnClickCallback(std::bind(&StartScene::OnClick, this, 1));
	AddNewControlObject(startbtn);
	AddNewObject(startbtntext = new Engine::Label("Start", "Inkfree.ttf", 56, halfW, halfH * 8 / 5, 0, 0, 0, 255, 0.5, 0.5));
	// BGM
	bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume, 0);
	// Turrets
	AddNewObject(TowerGroup = new Group());
	TowerGroup->AddNewObject(new MachineGunTurret(5 * blocksize, 8 * blocksize));
	TowerGroup->AddNewObject(new LightningTurret(10 * blocksize, 8 * blocksize));
	TowerGroup->AddNewObject(new MissileTurret(15 * blocksize, 8 * blocksize));
	TowerGroup->AddNewObject(new LaserTurret(20 * blocksize, 8 * blocksize));
	// Enemies
	AddNewObject(EnemyGroup = new Group());
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

void StartScene::OnMouseMove(int mx, int my)
{
	IScene::OnMouseMove(mx, my);
	if (startbtn->mouseIn == true)
		startbtntext->Color = al_map_rgb(255, 255, 255);
	else
		startbtntext->Color = al_map_rgb(0, 0, 0);
}
