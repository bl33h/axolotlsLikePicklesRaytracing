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
    // constructor to initialize Cube with minimum and maximum corners and material
    Cube(const glm::vec3& minCorner, const glm::vec3& maxCorner, const Material& mat);

    // function to perform ray intersection with the cube
    Intersect rayIntersect(const glm::vec3& rayOrigin, const glm::vec3& rayDirection) const override;

    // function to set the texture of the cube
    void setTexture(SDL_Texture* tex) {
        texture = tex;
    }

private:
    // minimum and maximum corners of the cube
    glm::vec3 minCorner;
    glm::vec3 maxCorner;

    // texture of the cube
    SDL_Texture* texture;
};