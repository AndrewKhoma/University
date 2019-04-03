// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#include "UI.h"

UI::UI(unsigned int width, unsigned int height, std::string program_name) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  win_width_ = width, win_height_ = height;
  window_ = glfwCreateWindow(width, height, program_name.c_str(), nullptr, nullptr);

  if (!window_) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(-1);
  }

  glfwMakeContextCurrent(window_);
  SetWindowCentered(window_);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    exit(-1);
  }

  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  glfwSetErrorCallback(GLFWErrorCallback);

  glfwSetWindowUserPointer(window_, this);
  glfwSetScrollCallback(window_, GLFWScrollCallback);

  glfwSetFramebufferSizeCallback(window_, GLFWFramebufferSizeCallback);
  glfwSetWindowFocusCallback(window_, GLFWWindowFocusCallback);
  glfwSetDropCallback(window_, GLFWDropCallback);
}

void UI::display() {
  std::vector<glm::vec2>
      glm_control_points{glm::vec2(2.0f, 2.0f), glm::vec2(4.0f, 4.0f), glm::vec2(6.0f, 4.0f), glm::vec2(9.0f, 1.0f)};

  glm::vec3 sum{0, 0, 0};
  for (auto control_point : glm_control_points) {
    sum += glm::vec3(control_point.x, control_point.y, -kZOffset);
  }
  sum /= glm_control_points.size();

  camera_ = new Camera(sum);

  std::vector<glm::vec2> glm_bezier_spline = Algorithm::Bezier(glm_control_points);
  std::vector<glm::vec2> glm_hermite_spline = Algorithm::Hermite(glm_control_points);

  float *control_points = CreateControlPoints(glm_control_points),
      *control_polyline = FromGLMVecToRawArray(glm_control_points),
      *bezier_spline = FromGLMVecToRawArray(glm_bezier_spline),
      *hermite_spline = FromGLMVecToRawArray(glm_hermite_spline);

  int ctrl_points_size = 4 * static_cast<int>(glm_control_points.size()),
      ctrl_polyline_size = static_cast<int>(glm_control_points.size()),
      bezier_spline_size = static_cast<int>(glm_bezier_spline.size()),
      hermite_spline_size = static_cast<int>(glm_hermite_spline.size());

  unsigned int VAO[kDrawableObjects], VBO[kDrawableObjects];

  glGenVertexArrays(kDrawableObjects, VAO);
  glGenBuffers(kDrawableObjects, VBO);

  for (int i = 0; i < kDrawableObjects; i++) {
    glBindVertexArray(VAO[i]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
    if (i == 0) {
      glBufferData(GL_ARRAY_BUFFER, ctrl_points_size * sizeof(float) * kDimension, control_points, GL_STATIC_DRAW);
    } else if (i == 1) {
      glBufferData(GL_ARRAY_BUFFER, ctrl_polyline_size * sizeof(float) * kDimension, control_polyline, GL_STATIC_DRAW);
    } else if (i == 2) {
      glBufferData(GL_ARRAY_BUFFER, bezier_spline_size * sizeof(float) * kDimension, bezier_spline, GL_STATIC_DRAW);
    } else if (i == 3) {
      glBufferData(GL_ARRAY_BUFFER, hermite_spline_size * sizeof(float) * kDimension, hermite_spline, GL_STATIC_DRAW);
    }

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(0);
  }

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_LINE_SMOOTH);

  Shader program("resources/shader.vert", "resources/shader.frag");
  program.Use();

  glm::mat4 model = glm::mat4(1.0f), projection, view;

  while (!glfwWindowShouldClose(window_)) {
    auto currentFrame = static_cast<float>(glfwGetTime());
    delta_time_ = currentFrame - last_frame_;
    last_frame_ = currentFrame;

    ProcessInput(window_);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    projection =
        glm::perspective(glm::radians(camera_->GetZoom()),
                         static_cast<float>(win_width_) / static_cast<float>(win_height_),
                         0.1f,
                         100.0f);

    // camera/view transformation
    view = camera_->GetViewMatrix();

    program.SetMat4f("model", model);
    program.SetMat4f("view", view);
    program.SetMat4f("projection", projection);

    // render control polyline
    program.SetVec3f("input_color", kOrangeColor);

    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_LINE_STRIP, 0, ctrl_polyline_size);

    // render control points
    program.SetVec3f("input_color", kBlackColor);

    glBindVertexArray(VAO[0]);
    glLineWidth(2.5);
    glDrawArrays(GL_LINES, 0, ctrl_points_size);
    glLineWidth(1.0);

    // render bezier spline
    program.SetVec3f("input_color", kRedColor);

    glBindVertexArray(VAO[2]);
    glDrawArrays(GL_LINE_STRIP, 0, bezier_spline_size);

    // render hermite spline
    program.SetVec3f("input_color", kBlueColor);

    glBindVertexArray(VAO[3]);
    glDrawArrays(GL_LINE_STRIP, 0, hermite_spline_size);

    glfwSwapBuffers(window_);
    glfwPollEvents();
  }

  glDeleteVertexArrays(kDrawableObjects, VAO);
  glDeleteBuffers(kDrawableObjects, VBO);

  delete camera_;
  delete[] control_points;
  delete[] control_polyline;
  delete[] bezier_spline;
  delete[] hermite_spline;
}

UI::~UI() {
  glfwDestroyWindow(window_);
  win_width_ = win_height_ = 0;
}

void UI::SetWindowCentered(GLFWwindow *window) {
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

void UI::GLFWErrorCallback(int error, const char *description) {
  std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

void UI::GLFWFramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  auto ui = static_cast<UI *>(glfwGetWindowUserPointer(window));
  ui->FramebufferSizeCallback(window, width, height);
}

void UI::FramebufferSizeCallback(GLFWwindow *, int width, int height) {
  glViewport(0, 0, width, height);
  win_width_ = static_cast<unsigned int>(width);
  win_height_ = static_cast<unsigned int>(height);
}

void UI::GLFWScrollCallback(GLFWwindow *window, double, double y_offset) {
  auto ui = static_cast<UI *>(glfwGetWindowUserPointer(window));
  ui->camera_->ProcessMouseScroll(static_cast<float>(y_offset));
}

void UI::GLFWWindowFocusCallback(GLFWwindow *window, int focused) {
  if (focused) {
    glfwRestoreWindow(window);
  } else {
    glfwIconifyWindow(window);
  }
}

void UI::GLFWDropCallback(GLFWwindow *, int count, const char **paths) {
  for (int i = 0; i < count; i++)
    std::cout << paths[i] << '\n';
}

float *UI::CreateControlPoints(const std::vector<glm::vec2> &points) {
  auto *result = new float[8 * points.size()];
  glm::vec2 temp;

  for (int i = 0; i < points.size(); i++) {
    temp = points[i] + left_top;
    result[8 * i] = temp.x, result[8 * i + 1] = temp.y;
    temp = points[i] + right_bottom;
    result[8 * i + 2] = temp.x, result[8 * i + 3] = temp.y;
    temp = points[i] + right_top;
    result[8 * i + 4] = temp.x, result[8 * i + 5] = temp.y;
    temp = points[i] + left_bottom;
    result[8 * i + 6] = temp.x, result[8 * i + 7] = temp.y;
  }

  return result;
}

void UI::ProcessInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera_->ProcessKeyboard(kUp, delta_time_);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera_->ProcessKeyboard(kDown, delta_time_);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera_->ProcessKeyboard(kLeft, delta_time_);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera_->ProcessKeyboard(kRight, delta_time_);
}

float *UI::FromGLMVecToRawArray(const std::vector<glm::vec2> &points) {
  auto *result = new float[2 * points.size()];

  for (int i = 0; i < points.size(); i++) {
    result[2 * i] = points[i].x;
    result[2 * i + 1] = points[i].y;
  }

  return result;
}
