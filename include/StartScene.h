#pragma once
#include "SceneManager.h"
#include "components.h"

class StartScene : public SceneManager {


    void Init() override; 

private:
    Object* start_button;
    Image* startBttn_image; 
};
