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

struct Material {
    Color diffuse;
    float albedo;
    float specularAlbedo;
    float specularCoefficient;
    float reflectivity;
    float transparency;
    float refractionIndex;
};

struct Light {
    glm::vec3 position;
    float intensity;
    Color color;

    Light(const glm::vec3& pos, float intensity, const Color& col)
        : position(pos), intensity(intensity), color(col) {}
    
};

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