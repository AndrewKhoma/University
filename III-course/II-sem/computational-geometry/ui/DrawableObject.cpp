//
// Created by ahoma on 03/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include "DrawableObject.h"

DrawableObject::DrawableObject(float *points, int size, GLenum drawing_mode) {
  points_ = points;
  size_ = size;
  mode_ = drawing_mode;
  glGenVertexArrays(1, &VAO_);
  glGenBuffers(1, &VBO_);
}

DrawableObject::~DrawableObject() {
  delete[] points_;
  glDeleteVertexArrays(1, &VAO_);
  glDeleteBuffers(1, &VBO_);
}
