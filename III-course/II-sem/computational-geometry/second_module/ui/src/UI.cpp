// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#include <UI.h>

#include "UI.h"

UI::UI(unsigned int width, unsigned int height, const std::string& program_name) {
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

  glfwSwapInterval(0);

  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  glfwSetErrorCallback(GLFWErrorCallback);

  glfwSetWindowUserPointer(window_, this);
  glfwSetScrollCallback(window_, GLFWScrollCallback);
  glfwSetMouseButtonCallback(window_, GLFWMouseButtonCallback);

  glfwSetFramebufferSizeCallback(window_, GLFWFramebufferSizeCallback);
  glfwSetWindowFocusCallback(window_, GLFWWindowFocusCallback);

  glEnable(GL_BLEND);
  glEnable(GL_POINT_SMOOTH);

  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  shader_program_ = Shader("resources/shader.vert", "resources/shader.frag");
  painter_ = DrawableObserver(&shader_program_, "input_color");
}

void UI::display(const glm::vec2 &top_left, const glm::vec2 &bottom_right) {
  // calculate center of mass
  glm::vec2 sum = (top_left + bottom_right) / 2.f;

  // calculate z offset, where you can see all the points
  float aspect = static_cast<float>(win_width_) / static_cast<float>(win_height_),
      tan_angle = tanf(glm::radians(Camera::kCameraDefaultZoom)),
      z_offset = kZMinOffset / tan_angle;

  for (auto control_point : {top_left, bottom_right}) {
    z_offset = std::max(z_offset,
                        (glm::distance(sum.y, control_point.y) + glm::distance(sum.x, control_point.x) * aspect)
                            / tan_angle);
  }

  camera_ = new Camera(glm::vec3(sum, z_offset));

  projection_ =
      glm::perspective(glm::radians(camera_->GetZoom()),
                       static_cast<float>(win_width_) / static_cast<float>(win_height_),
                       z_offset * 0.5f,
                       z_offset * 1.5f);
  inverse_projection_ = glm::inverse(projection_);

  DrawAxes();

  shader_program_.Use();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window_, true);
  ImGui_ImplOpenGL3_Init(shader_program_.GetGLSLVersion().c_str());

  shader_program_.SetMat4f("model", glm::mat4(1.0f));
  shader_program_.SetMat4f("projection", projection_);
  shader_program_.SetMat4f("view", camera_->GetViewMatrix());

  while (!glfwWindowShouldClose(window_)) {
    glfwPollEvents();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    DrawImGuiPanel();
    ImGui::Render();

    static float last_frame, current_frame;
    current_frame = static_cast<float>(glfwGetTime());
    delta_time_ = current_frame - last_frame;
    last_frame = current_frame;

    ProcessInput(window_);

    painter_.Draw();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window_);
  }

  delete camera_;
}

glm::dvec2 UI::FromNDCToWorldCoord(double x_pos, double y_pos) const {
  static glm::vec3 camera_position;
  static glm::vec4 camera_transformed;
  camera_position = camera_->GetPosition();
  static float w;
  camera_transformed =
      (projection_ * camera_->GetViewMatrix() * glm::vec4(camera_position.x, camera_position.y, 0, 1.0));
  w = camera_transformed.w, camera_transformed /= w;

  static glm::vec4 real_pos;
  real_pos =
      w * camera_->GetInverseViewMatrix() * inverse_projection_ * glm::vec4(x_pos, y_pos, camera_transformed.z, 1.0);

  return glm::dvec2(real_pos.x, real_pos.y);
}

glm::dvec2 UI::GetCursorPosition() const {
  static double x_pos, y_pos;
  glfwGetCursorPos(window_, &x_pos, &y_pos);

  double screen_x_pos = 2.0 * x_pos / static_cast<double>(win_width_) - 1.0,
      screen_y_pos = 1.0 - 2.0 * y_pos / static_cast<double>(win_height_);

  return FromNDCToWorldCoord(screen_x_pos, screen_y_pos);
}

double UI::GetCursorError() const {
  return glm::distance(FromNDCToWorldCoord(0, 0), FromNDCToWorldCoord(kCursorError, kCursorError));
}

void UI::DrawAxes() {
  glm::dvec2 x_min = FromNDCToWorldCoord(-1, 0),
      x_max = FromNDCToWorldCoord(1, 0), y_min = FromNDCToWorldCoord(0, -1), y_max = FromNDCToWorldCoord(0, 1);

  painter_.DeleteByName("axes grid");
  painter_.DeleteByName("axes");

  std::vector<glm::vec2> axes_grid =
      CreateAxesGrid(static_cast<int>(std::floor(x_min.x)),
                     static_cast<int>(std::ceil(x_max.x)),
                     static_cast<int>(std::floor(y_min.y)),
                     static_cast<int>(std::ceil(y_max.y)),
                     kGridScale, kGridStep);

  std::vector<glm::vec2>
      axes{glm::vec2(0, y_min.y), glm::vec2(0, y_max.y), glm::vec2(x_min.x, 0), glm::vec2(x_max.x, 0)};

  painter_.Add(new DrawableObject(axes_grid, GL_LINES, 0.5f), GLMColors::kBlackColor, "axes grid");
  painter_.Add(new DrawableObject(axes, GL_LINES, 5.0f), GLMColors::kBlackColor, "axes");
}

void UI::ProcessInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  static bool changed;
  changed = false;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    camera_->ProcessKeyboard(kUp, delta_time_), changed = true;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    camera_->ProcessKeyboard(kDown, delta_time_), changed = true;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    camera_->ProcessKeyboard(kLeft, delta_time_), changed = true;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    camera_->ProcessKeyboard(kRight, delta_time_), changed = true;

  if (changed) {
    DrawAxes();
    shader_program_.SetMat4f("view", camera_->GetViewMatrix());
  }
}

void UI::GLFWFramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  static UI *ui;
  ui = static_cast<UI *>(glfwGetWindowUserPointer(window));
  ui->FramebufferSizeCallback(window, width, height);
}

void UI::FramebufferSizeCallback(GLFWwindow *, int width, int height) {
  glViewport(0, 0, width, height);
  static float z_offset;

  z_offset = camera_->GetPosition().z;
  win_width_ = static_cast<unsigned int>(width);
  win_height_ = static_cast<unsigned int>(height);

  projection_ =
      glm::perspective(glm::radians(camera_->GetZoom()),
                       static_cast<float>(win_width_) / static_cast<float>(win_height_),
                       z_offset * 0.5f,
                       z_offset * 1.5f);
  inverse_projection_ = glm::inverse(projection_);
  shader_program_.SetMat4f("projection", projection_);

  DrawAxes();
}

void UI::GLFWScrollCallback(GLFWwindow *window, double x_offset, double y_offset) {
  static UI *ui;
  ui = static_cast<UI *>(glfwGetWindowUserPointer(window));
  ui->ScrollCallback(window, x_offset, y_offset);
}

void UI::ScrollCallback(GLFWwindow *, double, double y_offset) {
  camera_->ProcessMouseScroll(static_cast<float>(y_offset));
  static float z_offset;
  z_offset = camera_->GetPosition().z;

  projection_ =
      glm::perspective(glm::radians(camera_->GetZoom()),
                       static_cast<float>(win_width_) / static_cast<float>(win_height_),
                       z_offset * 0.5f,
                       z_offset * 1.5f);
  inverse_projection_ = glm::inverse(projection_);
  shader_program_.SetMat4f("projection", projection_);

  DrawAxes();
}

void UI::GLFWMouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
  static UI *ui;
  ui = static_cast<UI *>(glfwGetWindowUserPointer(window));
  ui->MouseButtonCallback(window, button, action, mods);
}

UI::~UI() {
  glfwDestroyWindow(window_);
  win_width_ = win_height_ = 0;
}

