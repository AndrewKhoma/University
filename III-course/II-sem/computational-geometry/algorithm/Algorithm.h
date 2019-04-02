// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#ifndef III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_ALGORITHM_ALGORITHM_H_
#define III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_ALGORITHM_ALGORITHM_H_

#include <vector>

#include <glm/glm.hpp>

class Algorithm {
  static constexpr int kIterationNum = static_cast<int>(1e4);

 public:
  static std::vector<glm::vec2> Bezier(const std::vector<glm::vec2> &points);

 private:
  static glm::vec2 BezierDeCasteljau(const std::vector<glm::vec2> &points, double u);
};

#endif  // III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_ALGORITHM_ALGORITHM_H_
