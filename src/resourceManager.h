/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: resourceManager.h
@version: I
Creation: 07/11/2023
Last modification: 21/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include <stdexcept>
#include "glm/glm.hpp"
#include <map>
#include <string>
#include "colors.h"
#define vprint(var) print(#var ":", var)

// helper function for printing a newline
inline void print() {
    std::cout << std::endl;
}

// helper function for printing the first item in a series
inline void printFirst(auto one, bool last = true) {
    std::cout << one;
    if (last) {
        std::cout << std::endl;
    }
}

// helper function for printing a series of items
inline void print(auto first, auto... args) {
    printFirst(first, false);

    if constexpr (sizeof...(args) > 0) {
        std::cout << ' '; 
        print(args...);    
    } else {
        std::cout << std::endl;
    }
}

// helper function for printing a glm::vec3 vector
inline void print(glm::vec3 v) {
    std::cout << "V3(" << v.x << ", " << v.y << "," << v.z << ")" << std::endl;
}

class resourceManager {
private:
    static std::map<std::string, SDL_Surface*> imageSurfaces;

public:
    // initialize the SDL_image library
    static void init() {
        int imgFlags = IMG_INIT_PNG;
    }

    // load an image from file and associate it with a key
    static void loadImage(const std::string& key, const char* path) {
        SDL_Surface* newSurface = IMG_Load(path);
        imageSurfaces[key] = newSurface;
    }

    // retrieve the color of a pixel from the specified image
    static Color getPixelColor(const std::string& key, int x, int y) {
        auto it = imageSurfaces.find(key);
        SDL_Surface* targetSurface = it->second;
        int bpp = targetSurface->format->BytesPerPixel;
        Uint8 *p = (Uint8 *)targetSurface->pixels + y * targetSurface->pitch + x * bpp;

        Uint32 pixelColor;
        switch (bpp) {
            case 1:
                pixelColor = *p;
                break;
            case 2:
                pixelColor = *(Uint16 *)p;
                break;
            case 3:
                if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                    pixelColor = p[0] << 16 | p[1] << 8 | p[2];
                } else {
                    pixelColor = p[0] | p[1] << 8 | p[2] << 16;
                }
                break;
            case 4:
                pixelColor = *(Uint32 *)p;
                break;
            default:
                throw std::runtime_error("Unknown format !");
        }

        SDL_Color color;
        SDL_GetRGB(pixelColor, targetSurface->format, &color.r, &color.g, &color.b);
        return Color{color.r, color.g, color.b};
    }

    // render the image onto the specified renderer
    static void render(SDL_Renderer* renderer, const std::string& key, int x, int y, int size = -1) {
        auto it = imageSurfaces.find(key);
        if (it == imageSurfaces.end()) {
            throw std::runtime_error("Image key not found!");
        }

        SDL_Surface* targetSurface = it->second;

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, targetSurface);
        if (!texture) {
            throw std::runtime_error("Unable to create texture from surface! SDL Error: " + std::string(SDL_GetError()));
        }

        SDL_Rect destRect;
        if (size == -1){
            destRect = { x, y, targetSurface->w, targetSurface->h };
        } else {
            destRect = { x, y, size, size };
        }
        SDL_RenderCopy(renderer, texture, NULL, &destRect);

        SDL_DestroyTexture(texture);
    }

    // cleanup resources
    static void cleanup() {
        for (auto& pair : imageSurfaces) {
            if (pair.second) {
                SDL_FreeSurface(pair.second);
            }
        }
        imageSurfaces.clear();
        IMG_Quit();
    }
};

// static initialization of the map
std::map<std::string, SDL_Surface*> resourceManager::imageSurfaces;