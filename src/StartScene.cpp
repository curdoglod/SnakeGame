#include "SceneDeclarations.h"


void StartScene::Init() {


    SetWindowSize(400, 700);
    start_button = CreateObject();
    start_button->AddComponent(new ButtonComponent([this]() { SwitchToScene(new GameScene()); }));
    startBttn_image = start_button->GetComponent<Image>(); 
    startBttn_image->SetSize(Vector2(150,50)); 
    start_button->SetPosition(GetWindowSize() / 2 - startBttn_image->GetSize()/2);
    start_button->AddComponent(new TextComponent(20, "Start Game", TextAlignment::CENTER)); 

}
