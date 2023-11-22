/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: cube.cpp
@version: I
Creation: 07/11/2023
Last modification: 21/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#include "cube.h"

Cube::Cube(const glm::vec3& minCorner, const glm::vec3& maxCorner, const Material& mat)
        : minCorner(minCorner), maxCorner(maxCorner), Object(mat) {}


Intersect Cube::rayIntersect(const glm::vec3& rayOrigin, const glm::vec3& rayDirection) const {
    glm::vec3 tMin = (minCorner - rayOrigin) / rayDirection;
    glm::vec3 tMax = (maxCorner - rayOrigin) / rayDirection;

    glm::vec3 t1 = glm::min(tMin, tMax);
    glm::vec3 t2 = glm::max(tMin, tMax);

    float tNear = glm::max(glm::max(t1.x, t1.y), t1.z);
    float tFar = glm::min(glm::min(t2.x, t2.y), t2.z);

    if (tNear > tFar || tFar < 0) {
        return Intersect{false};
    }

    glm::vec3 point = rayOrigin + tNear * rayDirection;

    glm::vec3 normal;
    if (point.x < minCorner.x + 1e-5) {
        normal = glm::vec3(-1.0f, 0.0f, 0.0f);
    } else if (point.x > maxCorner.x - 1e-5) {
        normal = glm::vec3(1.0f, 0.0f, 0.0f);
    } else if (point.y < minCorner.y + 1e-5) {
        normal = glm::vec3(0.0f, -1.0f, 0.0f);
    } else if (point.y > maxCorner.y - 1e-5) {
        normal = glm::vec3(0.0f, 1.0f, 0.0f);
    } else if (point.z < minCorner.z + 1e-5) {
        normal = glm::vec3(0.0f, 0.0f, -1.0f);
    } else if (point.z > maxCorner.z - 1e-5) {
        normal = glm::vec3(0.0f, 0.0f, 1.0f);
    }

    return Intersect{true, tNear, point, normal};
}