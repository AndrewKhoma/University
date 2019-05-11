// Copyright (c) 2019.
// Created by Andrii Khoma on 04/04/19.
// All rights reserved.

#include "GLFWUtility.h"

void SetWindowCentered(GLFWwindow *window) {
  int window_x, window_y;
  glfwGetWindowPos(window, &window_x, &window_y);

  int window_width, window_height;
  glfwGetWindowSize(window, &window_width, &window_height);

  window_width = static_cast<int>(window_width * 0.5);
  window_height = static_cast<int>(window_height * 0.5);

  window_x += window_width;
  window_y += window_height;

  int monitors_length;
  GLFWmonitor **monitors = glfwGetMonitors(&monitors_length);

  if (monitors == nullptr) {
    return;
  }

  GLFWmonitor *owner = nullptr;
  int owner_x = 0, owner_y = 0, owner_width = 0, owner_height = 0;

  for (int i = 0; i < monitors_length; i++) {
    int monitor_x, monitor_y;
    glfwGetMonitorPos(monitors[i], &monitor_x, &monitor_y);

    int monitor_width, monitor_height;
    auto *monitor_video_mode = const_cast<GLFWvidmode *> (glfwGetVideoMode(monitors[i]));

    if (monitor_video_mode == nullptr) {
      continue;

    } else {
      monitor_width = monitor_video_mode->width;
      monitor_height = monitor_video_mode->height;
    }

    if ((window_x > monitor_x && window_x < (monitor_x + monitor_width))
        && (window_y > monitor_y && window_y < (monitor_y + monitor_height))) {
      owner = monitors[i];

      owner_x = monitor_x;
      owner_y = monitor_y;

      owner_width = monitor_width;
      owner_height = monitor_height;
    }
  }

  if (owner != nullptr) {
    glfwSetWindowPos(window,
                     static_cast<int>(owner_x + (owner_width * 0.5) - window_width),
                     static_cast<int>(owner_y + (owner_height * 0.5) - window_height));
  }
}

void GLFWErrorCallback(int error, const char *description) {
  std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

void GLFWWindowFocusCallback(GLFWwindow *window, int focused) {
  if (focused) {
    glfwRestoreWindow(window);
  } else {
    glfwIconifyWindow(window);
  }
}

std::vector<glm::vec2> CreateAxesGrid(int x_min, int x_max, int y_min, int y_max, int scale, int step) {
  static std::vector<glm::vec2> axes;
  axes.clear();
  static int x_scale, x_step, y_scale, y_step;

  x_scale = (x_max - x_min) / scale;
  if ((x_max - x_min) % scale == 0 && x_scale > 0)
    x_scale--;

  y_scale = (y_max - y_min) / scale;
  if ((y_max - y_min) % scale == 0 && y_scale > 0)
    y_scale--;

  if (!x_scale)
    x_step = 1;
  else
    x_step = x_scale * step;

  if (!y_scale)
    y_step = 1;
  else
    y_step = y_scale * step;

  x_step = std::max(x_step, y_step);
  y_step = std::max(x_step, y_step);   // Make grid same size

  for (int x = x_min - x_min % x_step; x <= x_max; x += x_step) {
    axes.emplace_back(x, y_min);
    axes.emplace_back(x, y_max);
  }

  for (int y = y_min - y_min % y_step; y <= y_max; y += y_step) {
    axes.emplace_back(x_min, y);
    axes.emplace_back(x_max, y);
  }

  return axes;
}

bool operator<(const glm::vec2 &lhs, const glm::vec2 &rhs) {
  return lhs.x < rhs.x
      || (glm::epsilonEqual(static_cast<double>(lhs.x), static_cast<double>(rhs.x), kEpsGLM) && lhs.y < rhs.y);
}

bool operator<(const glm::dvec2 &lhs, const glm::dvec2 &rhs) {
  return lhs.x < rhs.x
      || (glm::epsilonEqual(static_cast<double>(lhs.x), static_cast<double>(rhs.x), kEpsGLM) && lhs.y < rhs.y);
}

bool operator>(const glm::vec2 &lhs, const glm::vec2 &rhs) { return rhs < lhs; }

bool operator>(const glm::dvec2 &lhs, const glm::dvec2 &rhs) { return rhs < lhs; }

bool operator<=(const glm::vec2 &lhs, const glm::vec2 &rhs) { return !(lhs > rhs); }

bool operator<=(const glm::dvec2 &lhs, const glm::dvec2 &rhs) { return !(lhs > rhs); }

bool operator>=(const glm::vec2 &lhs, const glm::vec2 &rhs) { return !(lhs < rhs); }

bool operator>=(const glm::dvec2 &lhs, const glm::dvec2 &rhs) { return !(lhs < rhs); }
