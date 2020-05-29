#ifndef DIRTYEFFECT_HPP
#define DIRTYEFFECT_HPP
#include <string>

#include "Sprite.hpp"

class PlayScene;
class StartScene;

class DirtyEffect : public Engine::Sprite {
protected:
	float timeSpan;
	float alpha;
	PlayScene* getPlayScene();
	StartScene* getStartScene();
public:
	DirtyEffect(std::string img, float timeSpan, float x, float y);
	void Update(float deltaTime) override;
};
#endif // DIRTYEFFECT_HPP
