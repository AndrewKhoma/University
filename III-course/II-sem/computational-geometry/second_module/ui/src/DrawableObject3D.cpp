//
// Created by ahoma on 11/05/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include "DrawableObject3D.h"

void DrawableObject3D::Init(float *points, int size, GLenum drawing_mode, float width) {
  points_ = points;
  size_ = size;
  mode_ = drawing_mode;
  width_ = width;

  glGenVertexArrays(1, &VAO_);
  glGenBuffers(1, &VBO_);

  glBindVertexArray(VAO_);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_);

  glBufferData(GL_ARRAY_BUFFER, size * sizeof(float) * kDimension, points, GL_STATIC_DRAW);

  glVertexAttribPointer(0, kDimension, GL_FLOAT, GL_FALSE, kDimension * sizeof(float), reinterpret_cast<void *>(0));
  glEnableVertexAttribArray(0);
}

float *FromGLMPointToRawArray(const glm::vec3 &point) {
  auto *result = new float[3];
  result[0] = point.x, result[1] = point.y, result[2] = point.z;
  return result;
}

DrawableObject3D::DrawableObject3D(const glm::vec3 &point, GLenum drawing_mode, float width) {
  float *raw_point = FromGLMPointToRawArray(point);
  int points_size = 1;
  Init(raw_point, points_size, drawing_mode, width);
}

DrawableObject3D::DrawableObject3D(const glm::vec2 &point, GLenum drawing_mode, float width) {
  float *raw_point = FromGLMPointToRawArray(glm::vec3(point, 0));
  int points_size = 1;
  Init(raw_point, points_size, drawing_mode, width);
}

void DrawableObject3D::Draw() {
  glBindVertexArray(VAO_);
  if (mode_ != GL_POINTS) {
    glLineWidth(width_);
  } else {
    glPointSize(width_);
  }

  glDrawArrays(mode_, 0, size_);

  if (mode_ != GL_POINTS) {
    glLineWidth(kDefaultWidth);
  } else {
    glPointSize(kDefaultWidth);
  }
}

float *FromGLMVecToRawArray3D(const std::vector<glm::vec3> &points) {
  auto *result = new float[3 * points.size()];

  for (int i = 0; i < points.size(); i++) {
    result[3 * i] = points[i].x;
    result[3 * i + 1] = points[i].y;
    result[3 * i + 2] = points[i].z;
  }
  return result;
}

float *FromGLMVecToRawArray3D(const std::vector<glm::vec2> &points) {
  std::vector<glm::vec3> new_points;
  new_points.reserve(points.size());
  for (auto point : points) {
    new_points.emplace_back(point, 0);
  }

  return FromGLMVecToRawArray3D(new_points);
}

DrawableObject3D::DrawableObject3D(const std::vector<glm::vec2> &points, GLenum drawing_mode, float width) {
  float *raw_points = FromGLMVecToRawArray3D(points);
  auto points_size = static_cast<int>(points.size());
  Init(raw_points, points_size, drawing_mode, width);
}

DrawableObject3D::DrawableObject3D(const std::vector<glm::vec3> &points, GLenum drawing_mode, float width) {
  float *raw_points = FromGLMVecToRawArray3D(points);
  auto points_size = static_cast<int>(points.size());
  Init(raw_points, points_size, drawing_mode, width);
}

DrawableObject3D::~DrawableObject3D() {
  delete[] points_;
  glDeleteVertexArrays(1, &VAO_);
  glDeleteBuffers(1, &VBO_);
}
