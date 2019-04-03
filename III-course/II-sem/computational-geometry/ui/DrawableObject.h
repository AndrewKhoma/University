//
// Created by ahoma on 03/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#ifndef III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_DRAWABLEOBJECT_H_
#define III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_DRAWABLEOBJECT_H_

#include <glad/glad.h>

class DrawableObject {
 public:
  DrawableObject(float *points, int size, GLenum drawing_mode);

  void Draw();

  ~DrawableObject();

 private:
  float *points_;
  int size_;
  unsigned int VAO_, VBO_;
  GLenum mode_;
};

#endif  // III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_DRAWABLEOBJECT_H_
