#include "sprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Utils.h"

//Sprite::Sprite(SDL_Texture* m_texture, SDL_Renderer* renderer)
//    : m_renderer(renderer), m_texture(m_texture) {
// 
//
//    // Set the initial size and position of the sprite
//    m_destRect.x =0 ;
//    m_destRect.y =0 ;
//    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_destRect.w, &m_destRect.h);
//
//    //setSize(m_destRect.y, m_destRect.y);
//}

Sprite::Sprite(const std::vector<unsigned char>& imageData, SDL_Renderer* renderer): m_renderer(renderer), m_texture(nullptr){

 
    SDL_RWops* rw = SDL_RWFromConstMem(imageData.data(), imageData.size());
    if (!rw) {
        std::cerr << "SDL_RWFromConstMem failed: " << SDL_GetError() << std::endl;
        return;
    }

 
    SDL_Surface* surface = IMG_Load_RW(rw, 1); 
    if (!surface) {
        std::cerr << "IMG_Load_RW failed: " << SDL_GetError() << std::endl;
        return;
    }

    
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); 

    if (!m_texture) {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
        return;
    }

    m_destRect.x = 0;
    m_destRect.y = 0;
    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_destRect.w, &m_destRect.h);
}

Sprite::~Sprite() {
    if (m_texture) {
        SDL_DestroyTexture(m_texture);
    }
}

void Sprite::draw() {
    SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &m_destRect, 0, nullptr, SDL_FLIP_NONE);

}

void Sprite::draw(const Vector2& vec2, float _angle) {
    setAngle(_angle); 
    m_destRect.x = (int)vec2.x;
    m_destRect.y = (int)vec2.y;
    SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &m_destRect, angle, nullptr, SDL_FLIP_NONE);
}

void Sprite::SetColorAndOpacity(Uint8 red, Uint8 green, Uint8 blue, float alpha) {

    SDL_SetTextureColorMod(m_texture, red, green, blue);
    SDL_SetTextureAlphaMod(m_texture, alpha*255); 
}

void Sprite::setPosition(int x, int y) {
    m_destRect.x = x;
    m_destRect.y = y;
}
void Sprite::setAngle(float angle) { this->angle = angle; }

void Sprite::setSize(int width, int height) {
    m_destRect.w = width;
    m_destRect.h = height;
}

Vector2  Sprite::getSize() {
    return Vector2(m_destRect.w, m_destRect.h);
}
