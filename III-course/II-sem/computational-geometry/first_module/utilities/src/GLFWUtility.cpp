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

std::vector<glm::vec2> CreateControlPoints(const std::vector<glm::vec2> &points) {
  std::vector<glm::vec2> result;
  glm::vec2 temp;

  for (auto point : points) {
    temp = point + left_top;
    result.push_back(temp);
    temp = point + right_bottom;
    result.push_back(temp);
    temp = point + right_top;
    result.push_back(temp);
    temp = point + left_bottom;
    result.push_back(temp);
  }

  return result;
}

std::vector<glm::vec2> CreateAxesGrid(int x_min, int x_max, int y_min, int y_max) {
  std::vector<glm::vec2> axes;
  for (int y = y_min; y <= y_max; y++) {
    axes.emplace_back(x_min, y);
    axes.emplace_back(x_max, y);
  }

  for (int x = x_min; x <= x_max; x++) {
    axes.emplace_back(x, y_min);
    axes.emplace_back(x, y_max);
  }

  return axes;
}
