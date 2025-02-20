#pragma once

#include "SceneManager.h"
#include "components.h"




class MainGameScene :public SceneManager {
public:
	void Init() override;

	void Update() override;
	~MainGameScene() {

	}
private:

	Sprite* bck = nullptr;
	Object* paddle = nullptr;
	Object* ball;
	Vector2* dir_ball;
	std::vector<Object*> blocks;
	Object* start_button = nullptr;
	Object* scoreObj;
	TextComponent* scoreText;
	int score;

};

