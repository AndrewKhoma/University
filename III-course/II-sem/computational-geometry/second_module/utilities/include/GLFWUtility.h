// Copyright (c) 2019.
// Created by Andrii Khoma on 04/04/19.
// All rights reserved.

#ifndef UTILITIES_INCLUDE_GLFWUTILITY_H_
#define UTILITIES_INCLUDE_GLFWUTILITY_H_

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

namespace GLMColors {
const glm::vec3
    kBlackColor = {0.f, 0.f, 0.f},
    kRedColor = {1.f, 0.f, 0.f},
    kGreenColor = {0.f, 1.f, 0.f};
};

const double kEpsGLM = 1e-9;

bool operator<(const glm::vec2 &lhs, const glm::vec2 &rhs);

bool operator<(const glm::dvec2 &lhs, const glm::dvec2 &rhs);

bool operator>(const glm::vec2 &lhs, const glm::vec2 &rhs);

bool operator>(const glm::dvec2 &lhs, const glm::dvec2 &rhs);

bool operator<=(const glm::vec2 &lhs, const glm::vec2 &rhs);

bool operator<=(const glm::dvec2 &lhs, const glm::dvec2 &rhs);

bool operator>=(const glm::vec2 &lhs, const glm::vec2 &rhs);

bool operator>=(const glm::dvec2 &lhs, const glm::dvec2 &rhs);

void SetWindowCentered(GLFWwindow *window);

void GLFWErrorCallback(int error, const char *description);

void GLFWWindowFocusCallback(GLFWwindow *window, int focused);

std::vector<glm::vec2> CreateAxesGrid(int x_min, int x_max, int y_min, int y_max, int scale, int step);

#pragma clang diagnostic pop

#endif  // UTILITIES_INCLUDE_GLFWUTILITY_H_

