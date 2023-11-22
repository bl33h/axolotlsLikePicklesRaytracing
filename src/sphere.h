/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: sphere.h
@version: I
Creation: 07/11/2023
Last modification: 21/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#pragma once
#include "object.h"
#include "materials.h"
#include "glm/glm.hpp"

class Sphere : public Object {
public:
    Sphere(const glm::vec3& center, float radius, const Material& mat);

    Intersect rayIntersect(const glm::vec3& rayOrigin, const glm::vec3& rayDirection) const override;

private:
    glm::vec3 center;
    float radius;
};