// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#ifndef CAMERA_INCLUDE_CAMERA_H_
#define CAMERA_INCLUDE_CAMERA_H_

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
  const float kZoomMax = 179.0f;
  const float kCameraSpeed = 2.5f;
  const float kCameraSensitivity = 0.1f;

 public:
  static constexpr float kCameraDefaultZoom = 45.0f;
  // Constructor with vectors
  explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                  glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f),
                  float zoom = kCameraDefaultZoom);

  // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
  glm::mat4 GetViewMatrix() const;

  glm::mat4 GetInverseViewMatrix() const;

  // Returns the camera zoom
  float GetZoom();

  // Processes input received from any keyboard-like input system.
  // Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
  void ProcessKeyboard(CameraMovement direction, float delta_time);

  // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
  void ProcessMouseMovement(float x_offset, float y_offset, bool constrain_pitch = true);

  // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
  void ProcessMouseScroll(float y_offset);

  glm::vec3 GetPosition() const;

 private:
  // Camera Attributes
  glm::vec3 position_{};
  glm::vec3 front_;
  glm::vec3 world_up_{}, up_{};
  glm::vec3 world_right_{}, right_{};

  glm::mat4 view_matrix_{}, inverse_view_matrix_{};

  // Camera options
  float movement_speed_;
  float zoom_;
  // Euler Angles
  float yaw_{};
  float pitch_{};

  // Calculates the front vector from the Camera's (updated) Euler Angles
  void UpdateCameraVectors();
};

#endif  // CAMERA_INCLUDE_CAMERA_H_

