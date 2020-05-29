#include <functional>
#include <string>

#include "AudioHelper.hpp"
#include "GameEngine.hpp"
#include "Image.hpp"
#include "ImageButton.hpp"
#include "Label.hpp"
#include "LoseScene.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

void LoseScene::Initialize() {
	// TODO 1 (2/2): You can imitate the 2 files: 'LoseScene.hpp', 'LoseScene.cpp' to implement your start scene.
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	// background image
	AddNewObject(new Engine::Image("play/GridLight.png", 0, 0, 1600, 833, 0, 0));
	AddNewObject(new Engine::Image("lose/benjamin-happy.png", halfW, halfH, 0, 0, 0.5, 0.5));
	AddNewObject(new Engine::Label("You Lose :(", "Inkfree.ttf", 75, halfW, halfH / 4 + 10, 0, 0, 0, 255, 0.5, 0.5));
	// button
	Engine::ImageButton* btn;
	Engine::Label* btntext;
	btn = new Engine::ImageButton("ButtonOut.png", "ButtonIn.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&LoseScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(btntext = new Engine::Label("Back", "Inkfree.ttf", 56, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
	btn->SetLabelBinding(btntext);
	// BGM
    bgmInstance = AudioHelper::PlaySample("astronomia.ogg", false, AudioHelper::BGMVolume, PlayScene::DangerTime);
}
void LoseScene::Terminate() {
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void LoseScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
