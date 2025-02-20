#ifndef TEXT_H
#define TEXT_H

#include "component.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>


enum class TextAlignment {
    LEFT,
    CENTER,
    RIGHT
};


class TextComponent : public Component {
public:
   
    

    /**
   Font Size
   Text
   Alignment TextAlignment::LEFT, CENTER RIGHT
  */
    TextComponent(int fontSize, const std::string& text, TextAlignment alignment = TextAlignment::LEFT)
        : text(text), color({0, 0, 0}), font(nullptr), texture(nullptr), fontSize(fontSize), m_renderer(nullptr), alignment(alignment){

    }

    ~TextComponent() {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
        if (font) {
            TTF_CloseFont(font);
        }

    }

    /**
    Text
   */
    void setText(const std::string& newText) {
        text = newText;
      
        if (texture) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }

        if (!font) {

            std::cerr << "Font not initialized" << std::endl;
            return;
        }
       
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        if (!surface) {
            std::cerr << "Failed to create surface: " << SDL_GetError() << std::endl;
            return;
        }

        texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        SDL_FreeSurface(surface);

       
    }

    /**
   Alignment TextAlignment::LEFT, CENTER RIGHT
  */
    void SetAlignment(TextAlignment newAlignment) {
        alignment = newAlignment;
    }

    void Init() override {

        m_renderer = object->GetRenderer();
        fontDataBuffer = Engine::GetDefaultArchive()->GetFile("Roboto-Black.ttf");
      

        SDL_RWops* rw = SDL_RWFromConstMem(fontDataBuffer.data(), fontDataBuffer.size());
        if (!rw) {
            std::cerr << "Failed to create SDL_RWops for font data." << std::endl;
            return;
        }

        font = TTF_OpenFontRW(rw, 1, fontSize);
         if (!font) {
              SDL_RWclose(rw);
          }

        setText(text);
    }

    void Update(float deltaTime) override {
        if (texture) {
            SDL_Rect renderQuad = { 0, 0, 0, 0 };
            SDL_QueryTexture(texture, NULL, NULL, &renderQuad.w, &renderQuad.h);

           
            Vector2 spriteSize = object->GetSize();

            //std :: cout << object->GetSize() <<std::endl; 
      
            switch (alignment) {
            case TextAlignment::LEFT:
                renderQuad.x = object->GetPosition().x ;
                break;
            case TextAlignment::CENTER:
                renderQuad.x = object->GetPosition().x - renderQuad.w / 2 + spriteSize.x / 2;
                break;
            case TextAlignment::RIGHT:
                renderQuad.x = object->GetPosition().x + spriteSize.x -  renderQuad.w;
                break;
            }

     
            renderQuad.y = object->GetPosition().y + (spriteSize.y - renderQuad.h) / 2;

            SDL_RenderCopy(m_renderer, texture, NULL, &renderQuad);
        }
    }

private:
    std::string text;
    SDL_Color color;
    TTF_Font* font;
    std::vector<unsigned char> fontDataBuffer;
    int fontSize; 
    SDL_Texture* texture;
    SDL_Renderer* m_renderer;
    TextAlignment alignment;
   
};

#endif // TEXT_COMPONENT_H
