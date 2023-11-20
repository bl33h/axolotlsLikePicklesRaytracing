/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: point.h
@version: I
Creation: 06/07/2023
Last modification: 11/07/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/

#pragma once
#include "colors.h"
#include <iostream>

struct Vertex {
  float x;
  float y;
  Color color;

  Vertex(float xCoord, float yCoord, const Color& c) : x(xCoord), y(yCoord), color(c) {}
};