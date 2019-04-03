// Copyright (c) 2019.
// Created by Andrii Khoma on 03/04/19.
// All rights reserved.

#ifndef III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_DRAWABLEOBSERVER_H_
#define III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_DRAWABLEOBSERVER_H_

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "DrawableObject.h"
#include "../shader/Shader.h"

class DrawableObserver {
 public:
  DrawableObserver();

  explicit DrawableObserver(Shader *shader, const std::string &uniform_name);

  void Add(DrawableObject *object, glm::vec3 color);

  void Draw();

  ~DrawableObserver();

 private:
  std::vector<DrawableObject *> objects_;
  std::vector<glm::vec3> colors_;

  Shader *shader_program_;
  std::string color_uniform_name_;
};

#endif  // III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_UI_DRAWABLEOBSERVER_H_
