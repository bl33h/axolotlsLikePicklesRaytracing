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

// struct representing information about the intersection of a ray with an object
struct Intersect {
    bool isIntersecting = false; // indicates whether the ray intersects with the object
    float dist = 0.0f;            // distance from the ray origin to the intersection point
    glm::vec3 point;              // intersection point coordinates
    glm::vec3 normal;             // normal vector at the intersection point
};

// abstract base class for objects in the scene
class Object {
public:
    // constructor with material initialization
    Object(const Material& mat) : material(mat) {}

    // virtual function for ray intersection, to be implemented by derived classes
    virtual Intersect rayIntersect(const glm::vec3& rayOrigin, const glm::vec3& rayDirection) const = 0;

    // material of the object
    Material material;
};