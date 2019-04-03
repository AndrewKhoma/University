// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#ifndef III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_UI_H_
#define III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_UI_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shader/Shader.h"
#include "../camera/Camera.h"
#include "../algorithm/Algorithm.h"

#include "DrawableObserver.h"

const float kDelta = 0.05f;

// TODO(ahoma): create file additions.h and replace all helpers right there

const glm::vec3
    kBlackColor = {0.0f, 0.0f, 0.0f},
    kRedColor = {1.f, 0.f, 0.f},
    kGreenColor = {0.f, 1.f, 0.f},
    kBlueColor = {0.f, 0.f, 1.f};

const glm::vec2
    left_top = {-kDelta, -kDelta},
    left_bottom = {-kDelta, kDelta},
    right_top = {kDelta, -kDelta},
    right_bottom = {kDelta, kDelta};

class UI {
  const float kZMinOffset = 0.01f;

  const int kMinX = -1000, kMaxX = 1000, kMinY = -1000, kMaxY = 1000;

 public:
  UI(unsigned int width, unsigned int height, std::string program_name);

  void display(const std::vector<glm::vec2> &points);

  ~UI();

 private:
  GLFWwindow *window_;
  Camera *camera_;
  unsigned int win_width_, win_height_;

  float delta_time_, last_frame_;

  Shader shader_program;
  DrawableObserver painter;

  void ProcessInput(GLFWwindow *window);

  static void GLFWFramebufferSizeCallback(GLFWwindow *window, int width, int height);

  void FramebufferSizeCallback(GLFWwindow *, int width, int height);

  static void GLFWScrollCallback(GLFWwindow *, double, double y_offset);

  static void GLFWDropCallback(GLFWwindow *, int count, const char **paths);
};

#endif  // III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_UI_H_
