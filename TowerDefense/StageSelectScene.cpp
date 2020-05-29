#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "AudioHelper.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"
#include "Label.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Resources.hpp"
#include "Slider.hpp"
#include "StageSelectScene.hpp"

void StageSelectScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
	// background image
	AddNewObject(new Engine::Image("play/GridLight.png", 0, 0, 1600, 833, 0, 0));
	// topic label
	AddNewObject(new Engine::Label("Stage Select", "Inkfree.ttf", 65, halfW, halfH / 4 + 10, 0, 0, 0, 255, 0.5, 0.5));
	Engine::Label* btntext = nullptr;
	Engine::ImageButton* btn = nullptr;
	// stage 1 button
    btn = new Engine::ImageButton("ButtonOut.png", "ButtonIn.png", halfW - 200, halfH / 2 , 400, 100);
	btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 1));
	AddNewControlObject(btn);
	AddNewObject(btntext = new Engine::Label("Stage 1", "Inkfree.ttf", 56, halfW, halfH / 2 + 50, 0, 0, 0, 255, 0.5, 0.5));
	btn->SetLabelBinding(btntext);
	// stage 2 button
	btn = new Engine::ImageButton("ButtonOut.png", "ButtonIn.png", halfW - 200, halfH / 2 + 150, 400, 100);
	btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(btntext = new Engine::Label("Stage 2", "Inkfree.ttf", 56, halfW, halfH / 2 + 200, 0, 0, 0, 255, 0.5, 0.5));
	btn->SetLabelBinding(btntext);
	// back button
	btn = new Engine::ImageButton("ButtonOut.png", "ButtonIn.png", halfW - 200, halfH / 2 + 450, 400, 100);
	btn->SetOnClickCallback(std::bind(&StageSelectScene::BackOnClick, this));
	AddNewControlObject(btn);
	AddNewObject(btntext = new Engine::Label("Back", "Inkfree.ttf", 56, halfW, halfH / 2 + 500, 0, 0, 0, 255, 0.5, 0.5));
	btn->SetLabelBinding(btntext);
	// two sliders
    Slider *sliderBGM, *sliderSFX;
    sliderBGM = new Slider(40 + halfW - 650, h - 200 - 2, 190, 4);
    sliderBGM->SetOnValueChangedCallback(std::bind(&StageSelectScene::BGMSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderBGM);
    AddNewObject(new Engine::Label("BGM: ", "Inkfree.ttf", 40, 40 + halfW - 60 - 650, h - 200, 0, 0, 0, 255, 0.5, 0.5));
    sliderSFX = new Slider(40 + halfW - 650, h - 100 - 2, 190, 4);
    sliderSFX->SetOnValueChangedCallback(std::bind(&StageSelectScene::SFXSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderSFX);
    AddNewObject(new Engine::Label("SFX: ", "Inkfree.ttf", 40, 40 + halfW - 60 - 650, h - 100, 0, 0, 0, 255, 0.5, 0.5));
    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
	bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
    sliderBGM->SetValue(AudioHelper::BGMVolume);
    sliderSFX->SetValue(AudioHelper::SFXVolume);
}
void StageSelectScene::Terminate() {
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void StageSelectScene::PlayOnClick(int stage) {
    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    scene->MapId = stage;
    Engine::GameEngine::GetInstance().ChangeScene("play");
}
void StageSelectScene::BackOnClick()
{
	Engine::GameEngine::GetInstance().ChangeScene("Start");
}
void StageSelectScene::BGMSlideOnValueChanged(float value) {
    AudioHelper::ChangeSampleVolume(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void StageSelectScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}

void StageSelectScene::OnMouseMove(int mx, int my)
{
	IScene::OnMouseMove(mx, my);
	/*for (auto it : UIbtnGroup->GetObjects())
	{
		if(dynamic_cast<Engine::ImageButton*>(it)->label == nullptr)
		if (dynamic_cast<Engine::ImageButton*>(it)->mouseIn)
			dynamic_cast<Engine::ImageButton*>(it)->label->Color = al_map_rgb(255, 255, 255);
		else
			dynamic_cast<Engine::ImageButton*>(it)->label->Color = al_map_rgb(0, 0, 0);
	}*/
}
