//
// Created by ahoma on 18/03/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#ifndef III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_SHADER_SHADER_H_
#define III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_SHADER_SHADER_H_

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
 public:
  Shader() : __id(0) {}

  Shader(const GLchar *vertex_shader_path, const GLchar *fragment_shader_path);

  void Use();

  void SetVec3f(const std::string &uniform_name, glm::vec3 value) const;

  void SetMat4f(const std::string &uniform_name, glm::mat4 value) const;

 private:
  unsigned int __id;
};

#endif  // III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_SHADER_SHADER_H_
