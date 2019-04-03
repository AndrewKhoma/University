// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#include "UI.h"

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

UI::UI(unsigned int width, unsigned int height, std::string program_name) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
  glfwWindowHint(GLFW_SAMPLES, 5);
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

  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  glfwSetErrorCallback(GLFWErrorCallback);

  glfwSetWindowUserPointer(window_, this);
  glfwSetScrollCallback(window_, GLFWScrollCallback);

  glfwSetFramebufferSizeCallback(window_, GLFWFramebufferSizeCallback);
  glfwSetWindowFocusCallback(window_, GLFWWindowFocusCallback);
  glfwSetDropCallback(window_, GLFWDropCallback);

  glEnable(GL_BLEND);

  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  shader_program = Shader("resources/shader.vert", "resources/shader.frag");
  painter = DrawableObserver(&shader_program, "input_color");
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

void UI::display(const std::vector<glm::vec2> &points) {
  // calculate center of mass
  glm::vec2 sum{0, 0};
  auto glm_ctrl_pts_size = static_cast<float>(points.size());
  for (auto control_point : points) {
    sum += control_point / glm_ctrl_pts_size;
  }

  // calculate z offset, where you can see all the points
  float z_offset = kZMinOffset,
      aspect = static_cast<float>(win_width_) / static_cast<float>(win_height_),
      tan_angle = tanf(glm::radians(Camera::kCameraDefaultZoom) / aspect);

  for (auto control_point : points) {
    z_offset = std::max(z_offset,
                        (glm::distance(sum.y, control_point.y) + glm::distance(sum.x, control_point.x) * aspect)
                            / tan_angle);
  }

  camera_ = new Camera(glm::vec3(sum, z_offset));

  std::vector<glm::vec2> control_points = CreateControlPoints(points);
  std::vector<glm::vec2> bezier_spline = Algorithm::Bezier(points);
  std::vector<glm::vec2> hermite_spline = Algorithm::Hermite(points);
  std::vector<glm::vec2> axes_grid = CreateAxesGrid(kMinX, kMaxX, kMinY, kMaxY);
  std::vector<glm::vec2> axes{glm::vec2(0, kMinY), glm::vec2(0, kMaxY), glm::vec2(kMinX, 0), glm::vec2(kMaxX, 0)};

  painter.Add(new DrawableObject(axes_grid, GL_LINES, 0.5f), kBlackColor);
  painter.Add(new DrawableObject(axes, GL_LINES, 5.0f), kBlackColor);
  painter.Add(new DrawableObject(points, GL_LINE_STRIP, 1.5f), kGreenColor);
  painter.Add(new DrawableObject(control_points, GL_LINES, 2.5f), kBlackColor);
  painter.Add(new DrawableObject(bezier_spline, GL_LINE_STRIP, 1.5f), kRedColor);
  painter.Add(new DrawableObject(hermite_spline, GL_LINE_STRIP, 1.5f), kBlueColor);

  shader_program.Use();

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
                         1.f,
                         z_offset * 1.5f);

    // camera/view transformation
    view = camera_->GetViewMatrix();

    shader_program.SetMat4f("model", model);
    shader_program.SetMat4f("view", view);
    shader_program.SetMat4f("projection", projection);

    painter.Draw();

    glfwSwapBuffers(window_);
    glfwPollEvents();
  }

  delete camera_;
}

UI::~UI() {
  glfwDestroyWindow(window_);
  win_width_ = win_height_ = 0;
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

void UI::GLFWDropCallback(GLFWwindow *, int count, const char **paths) {
  for (int i = 0; i < count; i++)
    std::cout << paths[i] << '\n';
}

void UI::ProcessInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    camera_->ProcessKeyboard(kUp, delta_time_);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    camera_->ProcessKeyboard(kDown, delta_time_);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    camera_->ProcessKeyboard(kLeft, delta_time_);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    camera_->ProcessKeyboard(kRight, delta_time_);
}
