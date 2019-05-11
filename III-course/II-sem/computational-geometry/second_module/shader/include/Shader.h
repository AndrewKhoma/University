//
// Created by ahoma on 18/03/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#ifndef SHADER_INCLUDE_SHADER_H_
#define SHADER_INCLUDE_SHADER_H_

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
 public:
  Shader() : id_(0) {}

  Shader(const GLchar *vertex_shader_path, const GLchar *fragment_shader_path);

  void Use();

  void SetVec3f(const std::string &uniform_name, glm::vec3 value) const;

  void SetMat4f(const std::string &uniform_name, glm::mat4 value) const;

  std::string GetGLSLVersion() const;

 private:
  unsigned int id_;
  std::string glsl_version_;
};

#endif  // SHADER_INCLUDE_SHADER_H_
