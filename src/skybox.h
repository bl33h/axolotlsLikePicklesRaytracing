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
    Skybox(const std::string& textureFile);
    ~Skybox();

    Color getColor(const glm::vec3& direction) const;

private:
    SDL_Surface* texture;
    void loadTexture(const std::string& textureFile);
};