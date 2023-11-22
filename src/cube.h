/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: cube.h
@version: I
Creation: 07/11/2023
Last modification: 21/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#pragma once
#include "object.h"
#include "materials.h"
#include "glm/glm.hpp"

class Cube : public Object {
public:
    Cube(const glm::vec3& minCorner, const glm::vec3& maxCorner, const Material& mat);

    Intersect rayIntersect(const glm::vec3& rayOrigin, const glm::vec3& rayDirection) const override;

    void setTexture(SDL_Texture* tex) {
        texture = tex;
    }

private:
    glm::vec3 minCorner;
    glm::vec3 maxCorner;
    SDL_Texture* texture;
};
