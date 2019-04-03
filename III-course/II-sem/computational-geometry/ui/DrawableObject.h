//
// Created by ahoma on 03/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#ifndef III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_DRAWABLEOBJECT_H_
#define III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_DRAWABLEOBJECT_H_

#include <glad/glad.h>

#include <vector>

#include <glm/glm.hpp>

class DrawableObject {
  static constexpr int kDimension = 2;
  static constexpr float kDefaultLineWidth = 1.0f;

 public:
  DrawableObject(const std::vector<glm::vec2> &points, GLenum drawing_mode, float line_width = kDefaultLineWidth);

  void Draw();

  ~DrawableObject();

 private:
  float *points_;
  int size_;

  unsigned int VAO_, VBO_;
  GLenum mode_;

  float line_width_;

  void Init(float *points, int size, GLenum drawing_mode, float line_width = kDefaultLineWidth);
};

#endif  // III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_DRAWABLEOBJECT_H_
