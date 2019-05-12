// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#ifndef UI_INCLUDE_UI_H_
#define UI_INCLUDE_UI_H_

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <utility>
#include <string>
#include <vector>

#include "Shader.h"
#include "Camera.h"
#include "GLFWUtility.h"

#include "../src/DrawableObserver.h"

class UI {
  const int kGridScale = 50, kGridStep = 5;

  const float kZMinOffset = 1.f,
      kCursorError = 0.01f;  // percentage from screen size, where 1 equals to whole screen

 public:
  UI(unsigned int width, unsigned int height, const std::string &program_name, unsigned int dimension = 2);

  void display(const glm::vec2 &top_left, const glm::vec2 &bottom_right);

  virtual ~UI();

 protected:
  virtual void DrawImGuiPanel() = 0;

  DrawableObserver painter_;

  virtual void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) = 0;

  glm::dvec2 GetCursorPosition() const;

  double GetCursorError() const;

  glm::dvec2 FromNDCToWorldCoord(double x_pos, double y_pos) const;

 private:
  GLFWwindow *window_;
  Camera *camera_{};
  Shader shader_program_;
  glm::mat4 projection_{}, inverse_projection_{};

  float delta_time_{};
  unsigned int win_width_, win_height_, dimension_;

  void DrawAxes();

  void ProcessInput(GLFWwindow *window);

  static void GLFWFramebufferSizeCallback(GLFWwindow *window, int width, int height);
  void FramebufferSizeCallback(GLFWwindow *, int width, int height);

  static void GLFWScrollCallback(GLFWwindow *window, double, double y_offset);
  void ScrollCallback(GLFWwindow *, double, double y_offset);

  static void GLFWMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

  static void GLFWMouseCallback(GLFWwindow *window, double x_pos, double y_pos);
  void MouseCallback(GLFWwindow *window, double x_pos, double y_pos);
};

#endif  // UI_INCLUDE_UI_H_
