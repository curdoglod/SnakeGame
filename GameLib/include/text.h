// text.h
#ifndef TEXT_H
#define TEXT_H

#include "component.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include "color.h"
#include <iostream>

enum class TextAlignment
{
    LEFT,
    CENTER,
    RIGHT
};

class TextComponent : public Component
{
public:
    TextComponent(int fontSize, const std::string &text, TextAlignment alignment = TextAlignment::LEFT)
        : text(text), color(0, 0, 0, 255), font(nullptr), texture(nullptr),
          fontSize(fontSize), m_renderer(nullptr), alignment(alignment)
    {
    }

    TextComponent(int fontSize, const std::string &text, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, TextAlignment alignment = TextAlignment::LEFT)
        : text(text), color(r, g, b, a), font(nullptr), texture(nullptr), fontSize(fontSize), m_renderer(nullptr), alignment(alignment) {}

    TextComponent(int fontSize, const std::string &text, const Color &color, TextAlignment alignment = TextAlignment::LEFT)
        : text(text), color(color), font(nullptr), texture(nullptr), fontSize(fontSize), m_renderer(nullptr), alignment(alignment) {}

    ~TextComponent()
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
        }
        if (font)
        {
            TTF_CloseFont(font);
        }
    }

    void setText(const std::string &newText)
    {
        text = newText;
        if (texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
        if (!font)
        {
            std::cerr << "Font not initialized" << std::endl;
            return;
        }
        SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
        if (!surface)
        {
            std::cerr << "Failed to create surface: " << SDL_GetError() << std::endl;
            return;
        }
        texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        SDL_FreeSurface(surface);
    }

    void SetAlignment(TextAlignment newAlignment)
    {
        alignment = newAlignment;
    }

    void setColor(const Color &newColor)
    {
        color = newColor;
        setText(text);
    }

    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
    {
        Color newColor(r, g, b, a);
        setColor(newColor);
    }

    void Init() override
    {
        m_renderer = object->GetRenderer();
        fontDataBuffer = Engine::GetDefaultArchive()->GetFile("Roboto-Black.ttf");
        SDL_RWops *rw = SDL_RWFromConstMem(fontDataBuffer.data(), fontDataBuffer.size());
        if (!rw)
        {
            std::cerr << "Failed to create SDL_RWops for font data." << std::endl;
            return;
        }
        font = TTF_OpenFontRW(rw, 1, fontSize);
        if (!font)
        {
            SDL_RWclose(rw);
        }
        setText(text);
    }
    
    virtual TextComponent* Clone() const override
    {
        return new TextComponent(fontSize, text, color, alignment);
    }

    void Update(float deltaTime) override
    {
        if (texture)
        {
            SDL_Rect renderQuad = {0, 0, 0, 0};
            SDL_QueryTexture(texture, NULL, NULL, &renderQuad.w, &renderQuad.h);
            Vector2 spriteSize = object->GetSize();
            switch (alignment)
            {
            case TextAlignment::LEFT:
                renderQuad.x = object->GetPosition().x;
                break;
            case TextAlignment::CENTER:
                renderQuad.x = object->GetPosition().x - renderQuad.w / 2 + spriteSize.x / 2;
                break;
            case TextAlignment::RIGHT:
                renderQuad.x = object->GetPosition().x + spriteSize.x - renderQuad.w;
                break;
            }
            renderQuad.y = object->GetPosition().y + (spriteSize.y - renderQuad.h) / 2;
            SDL_Point center = {renderQuad.w / 2, renderQuad.h / 2};
            SDL_RenderCopyEx(m_renderer, texture, NULL, &renderQuad, object->GetAngle(), &center, SDL_FLIP_NONE);
        }
    }

private:
    std::string text;
    Color color;
    TTF_Font *font;
    std::vector<unsigned char> fontDataBuffer;
    int fontSize;
    SDL_Texture *texture;
    SDL_Renderer *m_renderer;
    TextAlignment alignment;
};

#endif // TEXT_H