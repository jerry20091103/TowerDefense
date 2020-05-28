#ifndef STAGESELECTSCENE_HPP
#define STAGESELECTSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "IScene.hpp"
#include "Label.hpp"
#include "ImageButton.hpp"

class StageSelectScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
	explicit StageSelectScene() = default;
	void Initialize() override;
	void Terminate() override;
	void PlayOnClick(int stage);
	void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);
	void OnMouseMove(int mx, int my) override;
};

#endif // STAGESELECTSCENE_HPP
