/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: object.h
@version: I
Creation: 07/11/2023
Last modification: 21/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#pragma once
#include "materials.h"
#include "glm/glm.hpp"

struct Intersect {
    bool isIntersecting = false;
    float dist = 0.0f;
    glm::vec3 point;
    glm::vec3 normal;
};

class Object {
public:
    Object(const Material& mat) : material(mat) {}
    virtual Intersect rayIntersect(const glm::vec3& rayOrigin, const glm::vec3& rayDirection) const = 0;

    Material material;
};