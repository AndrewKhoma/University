// Copyright (c) 2019.
// Created by Andrii Khoma on 03/04/19.
// All rights reserved.

#ifndef UI_SRC_DRAWABLEOBSERVER_H_
#define UI_SRC_DRAWABLEOBSERVER_H_

#include <algorithm>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "DrawableObject.h"
#include "Shader.h"

class DrawableObserver {
 public:
  DrawableObserver();

  explicit DrawableObserver(Shader *shader, const std::string &uniform_name);

  void Add(DrawableObject *object, glm::vec3 color, const std::string &object_name);

  void DeleteByName(const std::string &object_name);

  void Draw();

  ~DrawableObserver();

 private:
  std::vector<DrawableObject *> objects_;
  std::vector<glm::vec3> colors_;
  std::vector<std::string> object_names_;

  Shader *shader_program_;
  std::string color_uniform_name_;
};

#endif  // UI_SRC_DRAWABLEOBSERVER_H_
