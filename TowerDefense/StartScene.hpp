#ifndef STARTSCENE_HPP
#define STARTSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "IScene.hpp"
#include "Label.hpp"
#include "ImageButton.hpp"

class StartScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
	Engine::Label* startbtntext;
	Engine::ImageButton* startbtn;
	Engine::Group* TowerGroup;
	Engine::Group* EnemyGroup;
	const int blocksize = 64;
	const int mapwidth = 25;
	const int mapheight = 13;
	explicit StartScene() = default;
	void Initialize() override;
	void Terminate() override;
	void OnClick(int stage); // start button
	void OnMouseMove(int, int) override;
};

#endif // STARTSCENE_HPP

