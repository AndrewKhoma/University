// Copyright (c) 2019.
// Created by Andrii Khoma on 11/04/19.
// All rights reserved.

#ifndef UTILITIES_INCLUDE_ALGORITHMUTILITY_H_
#define UTILITIES_INCLUDE_ALGORITHMUTILITY_H_

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

double Area(glm::vec2 a, glm::vec2 b, glm::vec2 c);

bool Clockwise(glm::vec2 a, glm::vec2 b, glm::vec2 c);

bool CounterClockwise(glm::vec2 a, glm::vec2 b, glm::vec2 c);

bool Parallel(glm::vec2 a, glm::vec2 b, glm::vec2 c);

glm::vec2 GetBottomRightPoint(const std::vector<glm::vec2> &points);

bool PointInsideConvex(const std::vector<glm::vec2> &points, glm::vec2 point);

double GetPolarAngle(glm::vec2 a, glm::vec2 b);

#endif  // UTILITIES_INCLUDE_ALGORITHMUTILITY_H_
