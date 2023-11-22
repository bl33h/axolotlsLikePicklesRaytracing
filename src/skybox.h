/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: skybox.h
@version: I
Creation: 07/11/2023
Last modification: 21/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#pragma once
#include "colors.h"
#include <string>
#include "glm/glm.hpp"

class Skybox {
public:
    // constructor: Initializes the Skybox with the specified texture file
    Skybox(const std::string& textureFile);

    // destructor: Frees the allocated texture surface
    ~Skybox();

    // retrieves the color of the skybox in the specified direction
    Color getColor(const glm::vec3& direction) const;

private:
    // surface to store the skybox texture
    SDL_Surface* texture;

    // loads the skybox texture from the specified file
    void loadTexture(const std::string& textureFile);
};