// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#ifndef III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_CAMERA_CAMERA_H_
#define III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_CAMERA_CAMERA_H_

#include <glad/glad.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement {
  kForward,
  kBackward,
  kUp,
  kDown,
  kLeft,
  kRight
};

class Camera {
  // Default camera values
  const float kCameraYaw = -90.0f;
  const float kCameraPitch = 0.0f;

  const float kZoomMin = 1.0f;
  const float kZoomMax = 150.0f;
  const float kCameraSpeed = 2.5f;

 public:
  static constexpr float kCameraDefaultZoom = 45.0f;
  // Constructor with vectors
  explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                  glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f),
                  float zoom = kCameraDefaultZoom);

  // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
  glm::mat4 GetViewMatrix();

  // Returns the camera zoom
  float GetZoom();

  // Processes input received from any keyboard-like input system.
  // Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
  void ProcessKeyboard(CameraMovement direction, float delta_time);

  // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
  void ProcessMouseScroll(float y_offset);

 private:
  // Camera Attributes
  glm::vec3 position_;
  glm::vec3 front_;
  glm::vec3 world_up_;
  glm::vec3 world_right_;

  // Camera options
  float movement_speed_;
  float zoom_;
};

#endif  // III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_CAMERA_CAMERA_H_

