#include <functional>
#include <string>

#include "StartScene.hpp"
#include "GameEngine.hpp"
#include "Image.hpp"
#include "Label.hpp"
#include "ImageButton.hpp"
#include "Point.hpp"
#include "AudioHelper.hpp"
#include "StageSelectScene.hpp"

void StartScene::Initialize()
{
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	// topic label
	AddNewObject(new Engine::Label("Tower Defense", "Inkfree.ttf", 72, halfW, halfH / 4 + 10, 255, 255, 255, 255, 0.5, 0.5));
	// start button
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 6 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&StartScene::OnClick, this, 1));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Start", "Inkfree.ttf", 48, halfW, halfH * 6 / 4, 0, 0, 0, 255, 0.5, 0.5));
	bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume, 0);
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
