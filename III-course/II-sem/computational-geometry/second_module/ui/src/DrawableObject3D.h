//
// Created by ahoma on 11/05/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#ifndef COMPUTATIONAL_GEOMETRY_DRAWABLEOBJECT3D_H
#define COMPUTATIONAL_GEOMETRY_DRAWABLEOBJECT3D_H

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

#include "DrawableObject.h"

class DrawableObject3D : public DrawableObject {
  static constexpr int kDimension = 3;
  static constexpr float kDefaultWidth = 1.0f;

 public:
  DrawableObject3D(const std::vector<glm::vec3> &points, GLenum drawing_mode, float width = kDefaultWidth);

  DrawableObject3D(const std::vector<glm::vec2> &points, GLenum drawing_mode, float width = kDefaultWidth);

  DrawableObject3D(const glm::vec3 &point, GLenum drawing_mode, float width = kDefaultWidth);

  DrawableObject3D(const glm::vec2 &point, GLenum drawing_mode, float width = kDefaultWidth);

  void Draw() override;

  ~DrawableObject3D();

 private:
  float *points_{};
  int size_{};

  unsigned int VAO_{}, VBO_{};
  GLenum mode_{};

  float width_{};

  void Init(float *points, int size, GLenum drawing_mode, float width = kDefaultWidth);
};

#endif //COMPUTATIONAL_GEOMETRY_DRAWABLEOBJECT3D_H
