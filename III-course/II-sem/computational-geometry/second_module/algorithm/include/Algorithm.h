// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#ifndef III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_ALGORITHM_INCLUDE_ALGORITHM_H_
#define III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_ALGORITHM_INCLUDE_ALGORITHM_H_

#include <vector>
#include <algorithm>
#include <glm/glm.hpp>

#include "tinynurbs.h"
#include "GLFWUtility.h"

class Algorithm {
  static constexpr int kBezierItNum = static_cast<int>(1e3);

 public:
  static std::vector<glm::vec2> Bezier(const std::vector<glm::vec2> &points);

  static tinynurbs::RationalSurface3f NURBSSurface(const std::vector<glm::vec3> &input_points);

  static std::vector<std::vector<glm::vec3>> NURBSPoints(const tinynurbs::RationalSurface3f& srf,
                                                         int u_points,
                                                         int v_points);

 private:
  static glm::vec2 BezierDeCasteljau(const std::vector<glm::vec2> &points, double u);
};

#endif  // III_COURSE_II_SEM_COMPUTATIONAL_GEOMETRY_ALGORITHM_INCLUDE_ALGORITHM_H_
