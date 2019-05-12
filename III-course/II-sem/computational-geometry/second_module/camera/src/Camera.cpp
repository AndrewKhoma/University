// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#include <Camera.h>

#include "../include/Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 right, float zoom) :
    front_(glm::vec3(0.0f, 0.0f, 1.0f)),
    movement_speed_(kCameraSpeed) {
  position_ = position;
  up_ = world_up_ = up;
  right_ = world_right_ = right;

  yaw_ = kCameraYaw;
  pitch_ = kCameraPitch;

  zoom_ = zoom;

  UpdateCameraVectors();
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
    position_ += right_ * velocity;
  if (direction == kLeft)
    position_ -= right_ * velocity;

  view_matrix_ = glm::lookAt(position_, position_ + front_, world_up_);
  inverse_view_matrix_ = glm::inverse(view_matrix_);
}

void Camera::ProcessMouseMovement(float x_offset, float y_offset, bool constrain_pitch) {
  x_offset *= kCameraSensitivity;
  y_offset *= kCameraSensitivity;

  yaw_ += x_offset;
  pitch_ += y_offset;

  // Make sure that when pitch is out of bounds, screen doesn't get flipped
  if (constrain_pitch) {
    if (pitch_ > 89.0f)
      pitch_ = 89.0f;
    if (pitch_ < -89.0f)
      pitch_ = -89.0f;
  }

  // Update Front, __right and Up Vectors using the updated Euler angles
  UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float y_offset) {
  if (kZoomMin <= zoom_ && zoom_ <= kZoomMax)
    zoom_ -= y_offset;
  if (zoom_ <= kZoomMin)
    zoom_ = kZoomMin;
  if (zoom_ >= kZoomMax)
    zoom_ = kZoomMax;
}

void Camera::UpdateCameraVectors() {
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

  view_matrix_ = glm::lookAt(position_, position_ + front_, up_);
  inverse_view_matrix_ = glm::inverse(view_matrix_);
}

float Camera::GetZoom() {
  return zoom_;
}

glm::vec3 Camera::GetPosition() const {
  return position_;
}

