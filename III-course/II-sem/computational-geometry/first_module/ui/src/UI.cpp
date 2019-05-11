// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#include "../include/UI.h"

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

void UI::display(const std::vector<glm::vec2> &points) {
  // calculate center of mass
  glm::vec2 sum{0, 0};
  auto glm_ctrl_pts_size = static_cast<float>(points.size());
  for (auto control_point : points) {
    sum += control_point / glm_ctrl_pts_size;
  }

  // calculate z offset, where you can see all the points
  float aspect = static_cast<float>(win_width_) / static_cast<float>(win_height_),
      tan_angle = tanf(glm::radians(Camera::kCameraDefaultZoom) / aspect),
      z_offset = kZMinOffset / tan_angle;

  for (auto control_point : points) {
    z_offset = std::max(z_offset,
                        (glm::distance(sum.y, control_point.y) + glm::distance(sum.x, control_point.x) * aspect)
                            / tan_angle);
  }

  camera_ = new Camera(glm::vec3(sum, z_offset));

  std::vector<glm::vec2> control_points,
      bezier_spline, hermite_spline;

  if (!points.empty()) {
    control_points = CreateControlPoints(points);
    bezier_spline = Algorithm::Bezier(points);
    hermite_spline = Algorithm::Hermite(points);
  }
  std::vector<glm::vec2> axes_grid = CreateAxesGrid(kMinX, kMaxX, kMinY, kMaxY);
  std::vector<glm::vec2> axes{glm::vec2(0, kMinY), glm::vec2(0, kMaxY), glm::vec2(kMinX, 0), glm::vec2(kMaxX, 0)};

  painter.Add(new DrawableObject(axes_grid, GL_LINES, 0.5f), GLMColors::kBlackColor);
  painter.Add(new DrawableObject(axes, GL_LINES, 5.0f), GLMColors::kBlackColor);
  painter.Add(new DrawableObject(points, GL_LINE_STRIP, 1.5f), GLMColors::kGreenColor);
  painter.Add(new DrawableObject(control_points, GL_LINES, 2.5f), GLMColors::kBlackColor);
  painter.Add(new DrawableObject(bezier_spline, GL_LINE_STRIP, 1.5f), GLMColors::kRedColor);
  painter.Add(new DrawableObject(hermite_spline, GL_LINE_STRIP, 1.5f), GLMColors::kBlueColor);

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
                         z_offset * 0.5f,
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
