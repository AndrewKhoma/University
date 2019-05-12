//
// Created by ahoma on 03/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include <stdexcept>
#include "DrawableObject.h"

void DrawableObject::Init(float *points, int size, GLenum drawing_mode, float width) {
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

float *FromGLMVecToRawArray(const std::vector<glm::vec2> &points) {
  auto *result = new float[2 * points.size()];

  for (int i = 0; i < points.size(); i++) {
    result[2 * i] = points[i].x;
    result[2 * i + 1] = points[i].y;
  }
  return result;
}

float *FromGLMPointToRawArray(const glm::vec2 &point) {
  auto *result = new float[2];
  result[0] = point.x, result[1] = point.y;
  return result;
}

DrawableObject::DrawableObject() {
  points_ = nullptr;
  size_ = 0;
  mode_ = GL_LINE_STRIP;
  width_ = 0;
}

DrawableObject::DrawableObject(const std::vector<glm::vec2> &points, GLenum drawing_mode, float width) {
  float *raw_points = FromGLMVecToRawArray(points);
  auto points_size = static_cast<int>(points.size());
  Init(raw_points, points_size, drawing_mode, width);
}

DrawableObject::DrawableObject(const glm::vec2 &point, GLenum drawing_mode, float width) {
  float *raw_point = FromGLMPointToRawArray(point);
  int points_size = 1;
  Init(raw_point, points_size, drawing_mode, width);
}

void DrawableObject::Draw() {
  if (points_ == nullptr) {
    throw std::logic_error("Can't render uninitialized object");
  }

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

DrawableObject::~DrawableObject() {
  if (points_) {
    delete[] points_;
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
  }
}


