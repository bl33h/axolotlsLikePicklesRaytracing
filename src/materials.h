/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: materials.h
@version: I
Creation: 07/11/2023
Last modification: 21/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#pragma once
#include "colors.h"
#include "glm/glm.hpp"

// struct representing material properties
struct Material {
    Color diffuse;            // Diffuse color of the material
    float albedo;             // Surface reflectivity
    float specularAlbedo;     // Specular reflection albedo
    float specularCoefficient; // Specular reflection coefficient
    float reflectivity;        // Reflectivity of the material
    float transparency;        // Transparency of the material
    float refractionIndex;     // Refraction index of the material
};

// struct representing a light source
struct Light {
    glm::vec3 position; // position of the light source
    float intensity; // intensity of the light
    Color color; // color of the light

    // constructor
    Light(const glm::vec3& pos, float intensity, const Color& col)
        : position(pos), intensity(intensity), color(col) {}
};

// external declarations of material instances
extern Material rubber;
extern Material grass;
extern Material mold;
extern Material lights;
extern Material carbon;
extern Material smile;
extern Material barbie;
extern Material popsicle;
extern Material straw;
extern Material coal;
extern Material darkCoal;
extern Material white;