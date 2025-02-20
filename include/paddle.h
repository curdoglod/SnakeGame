#pragma once
#include "component.h"
#include "iostream"
#include "math.h"
#include "SceneManager.h"

class PaddleComponent : public Component {
public:
  
    void Init() {
        std::vector<unsigned char> paddleImgData = Engine::GetResourcesArchive()->GetFile("paddle.png");
        object->AddComponent(new Image(paddleImgData));
        object->SetPosition(Vector2(175, 500));
    }
    
    void onKeyPressed(SDL_Keycode key) override {
      
        if (key == SDLK_LEFT) {
            moveDirection = -1;
         
        }
        else if (key == SDLK_RIGHT) {
            moveDirection = 1;
        }
        else if (key == SDLK_SPACE) {
			object->GetScene()->SwitchToScene(new MainGameScene());
		}
    }

    void onKeyReleased(SDL_Keycode key) override {
        if ((key == SDLK_RIGHT && moveDirection == 1) || ( key == SDLK_LEFT  && moveDirection == -1) ) {
            moveDirection = 0;
        }
    }

    void Update() override {
        if (object != nullptr&& moveDirection!=0) {
            windowSize = object->GetScene()->GetWindowSize();
            object->MoveX(moveDirection*20);
            if (object->GetPosition().x <= 0) object->SetPosition(Vector2(0, object->GetPosition().y));
            else if (object->GetPosition().x + object->GetSize().x >= windowSize.x)
                object->SetPosition(Vector2(windowSize.x - object->GetSize().x, object->GetPosition().y));
        }
    }

private:
    Vector2 windowSize; 
    int moveDirection = 0;
};
