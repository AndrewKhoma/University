//
// Created by ahoma on 03/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include "DrawableObject.h"

void DrawableObject::Init(float *points, int size, GLenum drawing_mode, float line_width) {
  points_ = points;
  size_ = size;
  mode_ = drawing_mode;
  line_width_ = line_width;

  glGenVertexArrays(1, &VAO_);
  glGenBuffers(1, &VBO_);

  glBindVertexArray(VAO_);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_);

  glBufferData(GL_ARRAY_BUFFER, size * sizeof(float) * kDimension, points, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast<void *>(0));
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

DrawableObject::DrawableObject(const std::vector<glm::vec2> &points, GLenum drawing_mode, float line_width) {
  float *raw_points = FromGLMVecToRawArray(points);
  auto points_size = static_cast<int>(points.size());
  Init(raw_points, points_size, drawing_mode, line_width);
}

void DrawableObject::Draw() {
  glBindVertexArray(VAO_);
  glLineWidth(line_width_);
  glDrawArrays(mode_, 0, size_);
  glLineWidth(kDefaultLineWidth);
}

DrawableObject::~DrawableObject() {
  delete[] points_;
  glDeleteVertexArrays(1, &VAO_);
  glDeleteBuffers(1, &VBO_);
}


