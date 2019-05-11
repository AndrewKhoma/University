// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#include <Camera.h>

#include "../include/Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 right, float zoom) :
    front_(glm::vec3(0.0f, 0.0f, 1.0f)),
    movement_speed_(kCameraSpeed) {
  position_ = position;
  world_up_ = up;
  world_right_ = right;

  zoom_ = zoom;

  glm::vec3 front;
  front.x = static_cast<float>(cos(glm::radians(kCameraYaw)) * cos(glm::radians(kCameraPitch)));
  front.y = static_cast<float>(sin(glm::radians(kCameraPitch)));
  front.z = static_cast<float>(sin(glm::radians(kCameraYaw)) * cos(glm::radians(kCameraPitch)));

  front_ = glm::normalize(front);
  view_matrix_ = glm::lookAt(position_, position_ + front_, world_up_);
  inverse_view_matrix_ = glm::inverse(view_matrix_);
}

glm::mat4 Camera::GetViewMatrix() const {
  return view_matrix_;
}

glm::mat4 Camera::GetInverseViewMatrix() const {
  return inverse_view_matrix_;
}

void Camera::ProcessKeyboard(CameraMovement direction, float delta_time) {
  float velocity = movement_speed_ * delta_time;

  if (direction == kForward)
    position_ += front_ * velocity;
  if (direction == kBackward)
    position_ -= front_ * velocity;
  if (direction == kUp)
    position_ += world_up_ * velocity;
  if (direction == kDown)
    position_ -= world_up_ * velocity;
  if (direction == kRight)
    position_ += world_right_ * velocity;
  if (direction == kLeft)
    position_ -= world_right_ * velocity;

  view_matrix_ = glm::lookAt(position_, position_ + front_, world_up_);
  inverse_view_matrix_ = glm::inverse(view_matrix_);
}

void Camera::ProcessMouseScroll(float y_offset) {
  if (kZoomMin <= zoom_ && zoom_ <= kZoomMax)
    zoom_ -= y_offset;
  if (zoom_ <= kZoomMin)
    zoom_ = kZoomMin;
  if (zoom_ >= kZoomMax)
    zoom_ = kZoomMax;
}

float Camera::GetZoom() {
  return zoom_;
}

glm::vec3 Camera::GetPosition() const {
  return position_;
}

