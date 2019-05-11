// Copyright (c) 2019.
// Created by Andrii Khoma on 03/04/19.
// All rights reserved.

#include "DrawableObserver.h"

DrawableObserver::DrawableObserver() {
  shader_program_ = nullptr;

  colors_.clear();
  objects_.clear();
}

DrawableObserver::DrawableObserver(Shader *shader, const std::string &uniform_name) :
    color_uniform_name_(uniform_name) {
  shader_program_ = shader;

  colors_.clear();
  objects_.clear();
}

void DrawableObserver::Add(DrawableObject *object, glm::vec3 color) {
  objects_.push_back(object);
  colors_.push_back(color);
}

void DrawableObserver::Draw() {
  auto all = static_cast<int>(objects_.size());
  for (int i = 0; i < all; i++) {
    shader_program_->SetVec3f(color_uniform_name_, colors_[i]);
    objects_[i]->Draw();
  }
}

DrawableObserver::~DrawableObserver() {
  shader_program_ = nullptr;
  color_uniform_name_ = "";

  auto all = static_cast<int>(objects_.size());
  for (int i = 0; i < all; i++) {
    delete objects_[i];
  }

  colors_.clear();
  objects_.clear();
}

