#pragma once
#include "component.h"
#include "iostream"
#include "math.h"
#include "SceneManager.h"

class SnakeComponent: public Component
{
public: 
    void Init() override
    {
        std::vector<unsigned char> paddleImgData = Engine::GetResourcesArchive()->GetFile("paddle.png");
        object->AddComponent(new Image(paddleImgData));
        object->SetPosition(Vector2(300, 300));
        
    }

    void Update(float deltaTime) override
    {
        Vector2 direction  = Vector2(1,1);
        object->SetPosition(object->GetPosition()+direction*deltaTime );
    }
};