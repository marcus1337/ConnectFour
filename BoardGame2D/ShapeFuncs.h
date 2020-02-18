#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <windows.h>

class ShapeFuncs {
public:

    static SDL_Texture* textureFromPath(std::string somePath, SDL_Renderer* renderer) {
        using namespace std;
        auto surface = IMG_Load(somePath.c_str());
        if (!surface) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", somePath.c_str(), NULL);

        }
        SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        return tmpTexture;
    }

    static SDL_Texture* textureBlank(int w, int h, SDL_Renderer* renderer) {
        SDL_Texture *Tile = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, w, h);
        return Tile;
    }

    static SDL_Texture* textureFromPath(SDL_Renderer* _renderer, std::string somePath) {
        auto surface = IMG_Load(somePath.c_str());
        if (!surface)
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to load image", NULL);
        SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(_renderer, surface);
        SDL_FreeSurface(surface);
        return tmpTexture;
    }

    static void setSurfaceAlpha(SDL_Surface *surface, Uint8 alpha)
    {
        if (!surface)
            return;

        SDL_PixelFormat* fmt = surface->format;
        if (fmt->Amask == 0) {
            SDL_SetSurfaceAlphaMod(surface, alpha);
        }
        else {
            unsigned bpp = fmt->BytesPerPixel;
            float scale = alpha / 255.0f;
            SDL_LockSurface(surface);
            for (int y = 0; y < surface->h; ++y)
                for (int x = 0; x < surface->w; ++x) {
                    Uint32* pixel_ptr = (Uint32 *)((Uint8 *)surface->pixels
                        + y * surface->pitch + x * bpp);
                    Uint8 r, g, b, a;
                    SDL_GetRGBA(*pixel_ptr, fmt, &r, &g, &b, &a);
                    *pixel_ptr = SDL_MapRGBA(fmt, r, g, b, scale * a);
                }
            SDL_UnlockSurface(surface);
        }
    }

};