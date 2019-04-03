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

class UI {
  static constexpr float kDelta = 0.05f;
  static constexpr float kZOffset = 7.5f;
  static constexpr int kDimension = 2;

  static constexpr int kDrawableObjects = 4;  // TODO(ahoma) : rewrite in observer pattern

  const glm::vec3 kBlackColor = {0.0f, 0.0f, 0.0f};
  const glm::vec3 kOrangeColor = {1.f, 0.532210107f, 0.f};
  const glm::vec3 kRedColor = {1.f, 0.f, 0.f};
  const glm::vec3 kBlueColor = {0.f, 0.f, 1.f};

  const glm::vec2 left_top = {-kDelta, -kDelta},
      left_bottom = {-kDelta, kDelta},
      right_top = {kDelta, -kDelta},
      right_bottom = {kDelta, kDelta};

 public:
  UI(unsigned int width, unsigned int height, std::string program_name);

  void display();

  ~UI();

 private:
  GLFWwindow *window_;
  Camera *camera_;
  unsigned int win_width_, win_height_;

  float delta_time_, last_frame_;

  float *CreateControlPoints(const std::vector<glm::vec2> &points);

  float *FromGLMVecToRawArray(const std::vector<glm::vec2> &points);

  void ProcessInput(GLFWwindow *window);

  void SetWindowCentered(GLFWwindow *window);

  static void GLFWErrorCallback(int error, const char *description);

  static void GLFWFramebufferSizeCallback(GLFWwindow *window, int width, int height);

  void FramebufferSizeCallback(GLFWwindow *, int width, int height);

  static void GLFWScrollCallback(GLFWwindow *, double, double y_offset);

  static void GLFWWindowFocusCallback(GLFWwindow *window, int focused);

  static void GLFWDropCallback(GLFWwindow *, int count, const char **paths);
};

#endif  // III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_UI_H_
