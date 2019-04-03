// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#ifndef III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_INCLUDE_UI_H_
#define III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_INCLUDE_UI_H_

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

#include "Shader.h"
#include "Camera.h"
#include "Algorithm.h"
#include "GLFWUtility.h"

#include "../src/DrawableObserver.h"

class UI {
  const float kZMinOffset = 1.f;

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
};

#endif  // III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_INCLUDE_UI_H_
