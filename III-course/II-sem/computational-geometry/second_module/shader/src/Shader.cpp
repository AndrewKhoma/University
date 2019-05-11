//
// Created by ahoma on 18/03/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include <Shader.h>

#include "../include/Shader.h"

void CheckCompileErrors(unsigned int shader, const std::string &type) {
  int success;
  char *info_log;
  int info_log_size;

  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_size);

      info_log = new char[info_log_size + 10];

      glGetShaderInfoLog(shader, info_log_size + 10, nullptr, info_log);
      std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << info_log
                << "\n ------------------------------------------------------- " << std::endl;

      delete[] info_log;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_size);

      info_log = new char[info_log_size + 10];

      glGetProgramInfoLog(shader, info_log_size + 10, nullptr, info_log);
      std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << info_log
                << "\n ------------------------------------------------------- " << std::endl;

      delete[] info_log;
    }
  }
}

Shader::Shader(const GLchar *vertex_shader_path, const GLchar *fragment_shader_path) {
  std::string vertex_code, fragment_code;
  std::ifstream vertex_shader_file, fragment_shader_file;

  vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    vertex_shader_file.open(vertex_shader_path);
    fragment_shader_file.open(fragment_shader_path);

    vertex_code =
        std::string(std::istreambuf_iterator<char>(vertex_shader_file.rdbuf()), std::istreambuf_iterator<char>());
    fragment_code =
        std::string(std::istreambuf_iterator<char>(fragment_shader_file.rdbuf()), std::istreambuf_iterator<char>());

    std::stringstream vertex_stream(vertex_code);
    while (glsl_version_.empty()) {
      std::getline(vertex_stream, glsl_version_);
    }
  } catch (std::istream::failure &e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    throw;
  }

  const char *vertex_source = vertex_code.c_str();
  const char *fragment_source = fragment_code.c_str();

  unsigned int vertex_id, fragment_id;

  vertex_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_id, 1, &vertex_source, nullptr);
  glCompileShader(vertex_id);
  CheckCompileErrors(vertex_id, "VERTEX");

  fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_id, 1, &fragment_source, nullptr);
  glCompileShader(fragment_id);
  CheckCompileErrors(fragment_id, "FRAGMENT");

  id_ = glCreateProgram();
  glAttachShader(id_, vertex_id);
  glAttachShader(id_, fragment_id);
  glLinkProgram(id_);
  CheckCompileErrors(id_, "PROGRAM");

  glDeleteShader(vertex_id);
  glDeleteShader(fragment_id);
}

void Shader::Use() {
  glUseProgram(id_);
}

void Shader::SetMat4f(const std::string &uniform_name, glm::mat4 value) const {
  glUniformMatrix4fv(glGetUniformLocation(id_, uniform_name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetVec3f(const std::string &uniform_name, glm::vec3 value) const {
  glUniform3f(glGetUniformLocation(id_, uniform_name.c_str()), value.x, value.y, value.z);
}

std::string Shader::GetGLSLVersion() const {
  return glsl_version_;
}

