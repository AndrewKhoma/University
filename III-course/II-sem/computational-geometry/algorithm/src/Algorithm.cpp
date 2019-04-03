// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#include "../include/Algorithm.h"

std::vector<glm::vec2> Algorithm::Bezier(const std::vector<glm::vec2> &points) {
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
std::vector<glm::vec2> Algorithm::Hermite(const std::vector<glm::vec2> &points) {
  std::vector<glm::vec2> derivatives(points.size());
  std::vector<float> vec_length(points.size());

  auto n = static_cast<int>(points.size());
  for (int i = 1; i < n; i++) {
    vec_length[i] = glm::distance(points[i - 1], points[i]);
  }

  for (int i = 1; i < n - 1; i++) {
    float enumerator = vec_length[i] + vec_length[i + 1];
    derivatives[i] = vec_length[i] * (points[i] - points[i - 1]) / enumerator
        + vec_length[i + 1] * (points[i + 1] - points[i]) / enumerator;
  }

  derivatives[0] = 2.0f * (points[1] - points[0]) - derivatives[1];
  derivatives[n - 1] = 2.0f * (points[n - 1] - points[n - 2]) - derivatives[n - 2];

  std::vector<glm::vec2> result;

  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j <= kHermiteItNum; j++) {
      result.push_back(HermiteCubic(points[i],
                                    points[i + 1],
                                    derivatives[i],
                                    derivatives[i + 1],
                                    static_cast<double>(j) / static_cast<double>(kHermiteItNum)));
    }
  }

  return result;
}

glm::vec2 Algorithm::HermiteCubic(const glm::vec2 &p0,
                                  const glm::vec2 &p1,
                                  const glm::vec2 &q0,
                                  const glm::vec2 &q1,
                                  double u) {
  double u_sq = u * u, u_cb = u_sq * u;
  return static_cast<float>(2.0 * u_cb - 3.0 * u_sq + 1) * p0 + static_cast<float>(u_cb - 2.0 * u_sq + u) * q0
      + static_cast<float>(-2.0 * u_cb + 3.0 * u_sq) * p1 + static_cast<float>(u_cb - u_sq) * q1;
}
