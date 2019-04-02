// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 right, float yaw, float pitch) :
    front_(glm::vec3(0.0f, 0.0f, 1.0f)),
    movement_speed_(kCameraSpeed),
    mouse_sensitivity_(kCameraSensitivity),
    zoom_(kCameraZoom) {

  position_ = position;
  world_up_ = up;
  world_right_ = right;
  yaw_ = yaw;
  pitch_ = pitch;

  UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
  return glm::lookAt(position_, position_ + front_, up_);
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
  if (direction == kLeft)
    position_ += world_right_ * velocity;
  if (direction == kRight)
    position_ -= world_right_ * velocity;
}

void Camera::ProcessMouseScroll(float y_offset) {
  if (zoom_ >= 1.0f && zoom_ <= 45.0f)
    zoom_ -= y_offset;
  if (zoom_ <= 1.0f)
    zoom_ = 1.0f;
  if (zoom_ >= 45.0f)
    zoom_ = 45.0f;
}

void Camera::UpdateCameraVectors() {
  // Calculate the new Front vector
  glm::vec3 front;
  front.x = static_cast<float>(cos(glm::radians(yaw_)) * cos(glm::radians(pitch_)));
  front.y = static_cast<float>(sin(glm::radians(pitch_)));
  front.z = static_cast<float>(sin(glm::radians(yaw_)) * cos(glm::radians(pitch_)));
  front_ = glm::normalize(front);

  // Also re-calculate the __right and Up vector
  // Normalize the vectors, because their length gets closer to 0 the more you look up or down
  // which results in slower movement.
  right_ = glm::normalize(glm::cross(front_, world_up_));
  up_ = glm::normalize(glm::cross(right_, front_));
}

float Camera::GetZoom() {
  return zoom_;
}
