// Copyright (c) 2019.
// Created by Andrii Khoma on 04/04/19.
// All rights reserved.

#ifndef III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UTILITIES_INCLUDE_GLFWUTILITY_H_
#define III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UTILITIES_INCLUDE_GLFWUTILITY_H_

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

namespace GLMColors {
const glm::vec3
    kBlackColor = {0.f, 0.f, 0.f},
    kRedColor = {1.f, 0.f, 0.f},
    kGreenColor = {0.f, 1.f, 0.f},
    kBlueColor = {0.f, 0.f, 1.f};
};

const float kDelta = 0.05f;

const glm::vec2
    left_top = {-kDelta, -kDelta},
    left_bottom = {-kDelta, kDelta},
    right_top = {kDelta, -kDelta},
    right_bottom = {kDelta, kDelta};

void SetWindowCentered(GLFWwindow *window);

void GLFWErrorCallback(int error, const char *description);

void GLFWWindowFocusCallback(GLFWwindow *window, int focused);

std::vector<glm::vec2> CreateControlPoints(const std::vector<glm::vec2> &points);

std::vector<glm::vec2> CreateAxesGrid(int x_min, int x_max, int y_min, int y_max);

#pragma clang diagnostic pop

#endif  // III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UTILITIES_INCLUDE_GLFWUTILITY_H_

