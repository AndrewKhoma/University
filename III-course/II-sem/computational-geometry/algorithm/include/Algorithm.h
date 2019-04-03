// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#ifndef III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_ALGORITHM_INCLUDE_ALGORITHM_H_
#define III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_ALGORITHM_INCLUDE_ALGORITHM_H_

#include <vector>

#include <glm/glm.hpp>

class Algorithm {
  static constexpr int kBezierItNum = static_cast<int>(1e4);
  static constexpr int kHermiteItNum = static_cast<int>(1e2);

 public:
  static std::vector<glm::vec2> Bezier(const std::vector<glm::vec2> &points);

  static std::vector<glm::vec2> Hermite(const std::vector<glm::vec2> &points);

 private:
  static glm::vec2 BezierDeCasteljau(const std::vector<glm::vec2> &points, double u);

  static glm::vec2 HermiteCubic(const glm::vec2 &p0,
                                const glm::vec2 &p1,
                                const glm::vec2 &q0,
                                const glm::vec2 &q1,
                                double u);
};

#endif  // III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_ALGORITHM_INCLUDE_ALGORITHM_H_
