#pragma once
#include "component.h"
#include "iostream"
#include "math.h"
#include "SceneManager.h"

class SnakeComponent : public Component
{
public:
    SnakeComponent(int block_size)
    {
        this->block_size = block_size;
    }

    void Init() override
    {
        head_downImgData = Engine::GetResourcesArchive()->GetFile("head_down.png");

        object->AddComponent(new Image(head_downImgData));
        object->SetPosition(Vector2(block_size * 8, block_size * 6));
        direction = Vector2(0, 1);
        queuedDirection = Vector2(0, 0);

        lastTurnPos = object->GetPosition();
    }

    void onKeyPressed(SDL_Keycode key) override
    {
        Vector2 currentPos = object->GetPosition();
        float distanceSinceTurn = (currentPos - lastTurnPos).length();
        if (distanceSinceTurn < block_size * 0.4f)
        {
            return;
        }

        if (queuedDirection.x != 0 || queuedDirection.y != 0)
        {
            return;
        }

        Vector2 newDir(0, 0);
        if (key == SDLK_d)
            newDir = Vector2(1, 0);
        else if (key == SDLK_a)
            newDir = Vector2(-1, 0);
        else if (key == SDLK_w)
            newDir = Vector2(0, -1);
        else if (key == SDLK_s)
            newDir = Vector2(0, 1);
        else
            return;

        if (newDir.x == -direction.x && newDir.y == -direction.y)
            return;

        queuedDirection = newDir;
        UpdateSprite(newDir);
    }

    void onKeyReleased(SDL_Keycode key) override
    {
    }

    void Update(float deltaTime) override
    {
        Vector2 pos = object->GetPosition();
        pos += direction * deltaTime * speed;

        const float epsilon = 1.0f;

        bool aligned = false;
        if (direction.x != 0)
        {
            float targetY = round(pos.y / block_size) * block_size;
            aligned = fabs(pos.y - targetY) < epsilon;
        }
        else if (direction.y != 0)
        {
            float targetX = round(pos.x / block_size) * block_size;
            aligned = fabs(pos.x - targetX) < epsilon;
        }

        if (aligned && (queuedDirection.x != 0 || queuedDirection.y != 0))
        {
            if (queuedDirection.x != 0)
            {
                pos.y = round(pos.y / block_size) * block_size;
            }
            else if (queuedDirection.y != 0)
            {
                pos.x = round(pos.x / block_size) * block_size;
            }
            direction = queuedDirection;
            queuedDirection = Vector2(0, 0);

            lastTurnPos = pos;
        }

        object->SetPosition(pos);
    }

private:
    void UpdateSprite(const Vector2 &dir)
    {
        if (dir.x > 0)
            object->SetRotation(270);
        else if (dir.x < 0)
            object->SetRotation(90);
        else if (dir.y < 0)
            object->SetRotation(180);
        else if (dir.y > 0)
            object->SetRotation(0);
    }

    Vector2 direction;
    Vector2 queuedDirection;
    Vector2 lastTurnPos;

    float speed = 100.0f;
    std::vector<unsigned char> head_downImgData;
    std::vector<Object *> body;
    int block_size;
};