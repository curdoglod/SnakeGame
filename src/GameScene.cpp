#include "SceneDeclarations.h"

void GameScene::Init()
{
    GenBackground(); 
    Object* snake = CreateObject(); 
    snake->AddComponent(new SnakeComponent()); 
}

void GameScene::Update()
{
}


void GameScene::GenBackground()
{
    std::vector<unsigned char> block_light_img = Engine::GetResourcesArchive()->GetFile("block_sgreen.png");
    std::vector<unsigned char> block_dark_img = Engine::GetResourcesArchive()->GetFile("block_tgreen.png");

    for (int j = 0; j < GetWindowSize().y / 40; j++)
        for (int i = 0; i < GetWindowSize().x / 40; i++)
        {
            Object *block_background = CreateObject();
            block_background->SetPosition(Vector2(i * 40, j * 40));

            if ((i % 2 == 1 && j%2 == 0)||(i % 2 == 0 && j%2 == 1))
            {
                block_background->AddComponent(new Image(block_dark_img));
            }
            else
            {
                block_background->AddComponent(new Image(block_light_img));
            }
        }

}