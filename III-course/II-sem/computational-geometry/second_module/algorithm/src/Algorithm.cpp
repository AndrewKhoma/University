// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#include "../include/Algorithm.h"

std::vector<glm::vec2> Algorithm::Bezier(const std::vector<glm::vec2> &points) {
  if (points.empty())
    return std::vector<glm::vec2>();

  std::vector<glm::vec2> result;

  for (int i = 0; i <= kBezierItNum; i++) {
    result.push_back(BezierDeCasteljau(points, static_cast<double>(i) / static_cast<double>(kBezierItNum)));
  }

  return result;
}

glm::vec2 Algorithm::BezierDeCasteljau(const std::vector<glm::vec2> &points, double u) {
  std::vector<glm::vec2> comp_p(points);
  auto n = static_cast<int>(points.size());

  for (int k = 1; k < n; k++) {
    for (int i = 0; i < (n - k); i++) {
      comp_p[i].x = static_cast<float>((1.0 - u) * comp_p[i].x + u * comp_p[i + 1].x);
      comp_p[i].y = static_cast<float>((1.0 - u) * comp_p[i].y + u * comp_p[i + 1].y);
    }
  }

  return comp_p[0];
}
