#pragma once



class GameScene :public SceneManager
{
public:
	void Init() override;

	void Update() override;

private:
	void GenBackground();

};

