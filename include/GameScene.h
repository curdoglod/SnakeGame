#pragma once



class GameScene :public SceneManager
{
public:
	void Init() override;

	void Update() override;

private:
	void GenBackground();
	Vector2 RandomApple();
	Object* apple;
	int block_size; 
	Object* snake; 
	Vector2 block_count;
	Object* scoreObj; 
	int appleCount; 
};

