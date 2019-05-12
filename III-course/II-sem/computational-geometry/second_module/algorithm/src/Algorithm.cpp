// Copyright (c) 2019.
// Created by Andrii Khoma on 02/04/19.
// All rights reserved.

#include "Algorithm.h"

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

tinynurbs::RationalSurface3f Algorithm::NURBSSurface(const std::vector<glm::vec3> &input_points) {
  if (input_points.size() != 8)
    throw std::logic_error("not implemented");

  std::vector<glm::vec3> points = input_points;

  std::sort(points.begin(), points.end());
  tinynurbs::RationalSurface3f result;
  result.degree_u = 3;
  result.degree_v = 1;
  result.knots_u = {0, 0, 0, 0, 1, 1, 1, 1};
  result.knots_v = {0, 0, 1, 1};
  result.control_points = {4, 2, points};
  result.weights = {4, 2,
                    {1, 1,
                     1.f / 3.f, 1.f / 3.f,
                     1.f / 3.f, 1.f / 3.f,
                     1, 1
                    }
  };

  if (tinynurbs::surfaceIsValid(result))
    return result;
  else
    throw std::logic_error("Incorrect surface");
}

std::vector<std::vector<glm::vec3>> Algorithm::NURBSPoints(const tinynurbs::RationalSurface3f &srf,
                                                           int u_points,
                                                           int v_points) {
  std::vector<std::vector<glm::vec3>> result;
  for (int i = 0; i <= u_points; i++) {
    result.emplace_back();
    for (int j = 0; j <= v_points; j++) {
      result.back().push_back(tinynurbs::surfacePoint(srf,
                                                      static_cast<float>(i) / static_cast<float>(u_points),
                                                      static_cast<float>(j) / static_cast<float>(v_points)));
    }
  }

  for (int j = 0; j <= v_points; j++) {
    result.emplace_back();
    for (int i = 0; i <= u_points; i++) {
      result.back().push_back(tinynurbs::surfacePoint(srf,
                                                      static_cast<float>(i) / static_cast<float>(u_points),
                                                      static_cast<float>(j) / static_cast<float>(v_points)));
    }
  }
  return result;
}

