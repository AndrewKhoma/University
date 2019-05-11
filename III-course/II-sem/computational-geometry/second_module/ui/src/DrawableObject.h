//
// Created by ahoma on 03/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#ifndef UI_SRC_DRAWABLEOBJECT_H_
#define UI_SRC_DRAWABLEOBJECT_H_

#include <glad/glad.h>

#include <vector>

#include <glm/glm.hpp>

class DrawableObject {
  static constexpr int kDimension = 2;
  static constexpr float kDefaultWidth = 1.0f;

 public:
  DrawableObject(const std::vector<glm::vec2> &points, GLenum drawing_mode, float width = kDefaultWidth);

  DrawableObject(const glm::vec2 &point, GLenum drawing_mode, float width = kDefaultWidth);

  void Draw();

  ~DrawableObject();

 private:
  float *points_;
  int size_;

  unsigned int VAO_, VBO_;
  GLenum mode_;

  float width_;

  void Init(float *points, int size, GLenum drawing_mode, float width = kDefaultWidth);
};

#endif  // UI_SRC_DRAWABLEOBJECT_H_
