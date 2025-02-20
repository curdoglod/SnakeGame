#include "SceneDeclarations.h"

void GameScene::Init()
{
    block_size = 40;
    block_count = GetWindowSize()/block_size; 
    GenBackground();

    snake = CreateObject();
    snake->AddComponent(new SnakeComponent(block_size));
    apple = CreateObject();
    apple->SetLayer(5);
    snake->SetLayer(10);
    std::vector<unsigned char> appleImg = Engine::GetResourcesArchive()->GetFile("apple.png");

    apple->AddComponent(new Image(appleImg));
    apple->SetPosition(Vector2(rand() % (int)block_count.x * block_size, rand() % (int)block_count.y * block_size));
    while (apple->Crossing(snake))
    {
        apple->SetPosition(Vector2(rand() % 10 * block_size, rand() % 14 * block_size));
    }
}

void GameScene::Update()
{
    if (apple->Crossing(snake, 0.5,0.5))
    {
        while (apple->Crossing(snake))
        {
            apple->SetPosition(Vector2(rand() % 10 * block_size, rand() % 14 * block_size));
        }
    }
}

void GameScene::GenBackground()
{
    std::vector<unsigned char> block_light_img = Engine::GetResourcesArchive()->GetFile("block_sgreen.png");
    std::vector<unsigned char> block_dark_img = Engine::GetResourcesArchive()->GetFile("block_tgreen.png");

    for (int j = 0; j < block_count.y; j++)
        for (int i = 0; i < block_count.x; i++)
        {
            Object *block_background = CreateObject();
            block_background->SetPosition(Vector2(i * block_size, j * block_size));

            if ((i % 2 == 1 && j % 2 == 0) || (i % 2 == 0 && j % 2 == 1))
            {
                block_background->AddComponent(new Image(block_dark_img));
            }
            else
            {
                block_background->AddComponent(new Image(block_light_img));
            }
        }
}