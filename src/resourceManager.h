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

inline void print() {
    std::cout << std::endl;
}

inline void printFirst(auto one, bool last = true) {
    std::cout << one;
    if (last) {
        std::cout << std::endl;
    }
}

inline void print(auto first, auto... args) {
    printFirst(first, false);

    if constexpr (sizeof...(args) > 0) {
        std::cout << ' '; 
        print(args...);    
    } else {
        std::cout << std::endl;
    }
}

inline void print(glm::vec3 v) {
    std::cout << "V3(" << v.x << ", " << v.y << "," << v.z << ")" << std::endl;
}

class resourceManager {
private:
    static std::map<std::string, SDL_Surface*> imageSurfaces;
public:
    // Initialize SDL_image
    static void init() {
        int imgFlags = IMG_INIT_PNG; // or IMG_INIT_JPG, depending on your needs
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            throw std::runtime_error("SDL_image could not initialize! SDL_image Error: " + std::string(IMG_GetError()));
        }
    }

    // Load an image from a given path and store with a key
    static void loadImage(const std::string& key, const char* path) {
        SDL_Surface* newSurface = IMG_Load(path);
        if (!newSurface) {
            throw std::runtime_error("Unable to load image! SDL_image Error: " + std::string(IMG_GetError()));
        }
        imageSurfaces[key] = newSurface;
    }

    // Get the color of the pixel at (x, y) from an image with a specific key
    static Color getPixelColor(const std::string& key, int x, int y) {
        auto it = imageSurfaces.find(key);
        if (it == imageSurfaces.end()) {
            throw std::runtime_error("Image key not found!");
        }

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
                throw std::runtime_error("Unknown format!");
        }

        SDL_Color color;
        SDL_GetRGB(pixelColor, targetSurface->format, &color.r, &color.g, &color.b);
        return Color{color.r, color.g, color.b};
    }

    static void render(SDL_Renderer* renderer, const std::string& key, int x, int y, int size = -1) {
        auto it = imageSurfaces.find(key);
        if (it == imageSurfaces.end()) {
            throw std::runtime_error("Image key not found!");
        }

        SDL_Surface* targetSurface = it->second;

        // Convert surface to texture
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, targetSurface);
        if (!texture) {
            throw std::runtime_error("Unable to create texture from surface! SDL Error: " + std::string(SDL_GetError()));
        }

        // Set render destination and render the texture
        SDL_Rect destRect;
        if (size == -1){
            destRect = { x, y, targetSurface->w, targetSurface->h };
        } else {
            destRect = { x, y, size, size };
        }
        SDL_RenderCopy(renderer, texture, NULL, &destRect);

        // Free the created texture
        SDL_DestroyTexture(texture);
    }

    // Clean up
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

std::map<std::string, SDL_Surface*> resourceManager::imageSurfaces;