// Copyright (c) 2019.
// Created by Andrii Khoma on 11/04/19.
// All rights reserved.

#include "AlgorithmUtility.h"

const double kEps = 1e-9;

double Area(glm::vec2 a, glm::vec2 b, glm::vec2 c) {
  return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

bool Clockwise(glm::vec2 a, glm::vec2 b, glm::vec2 c) {
  return Area(a, b, c) < 0;
}

bool CounterClockwise(glm::vec2 a, glm::vec2 b, glm::vec2 c) {
  return Area(a, b, c) > 0;
}

bool Parallel(glm::vec2 a, glm::vec2 b, glm::vec2 c) {
  return Area(a, b, c) == 0;
}

glm::vec2 GetBottomRightPoint(const std::vector<glm::vec2> &points) {
  glm::vec2 bottom_right = points.front();
  static glm::bvec2 comparison;

  for (auto point : points) {
    comparison = glm::lessThan(point, bottom_right);
    if (comparison[1] || (comparison[1] && !comparison[0]))
      bottom_right = point;
  }

  return bottom_right;
}

bool PointInsideConvex(const std::vector<glm::vec2> &points, glm::vec2 point) {
  if (points.size() <= 2)
    return false;

  bool result_clockwise = Clockwise(points.back(), points.front(), point),
      result_counter_clockwise = CounterClockwise(points.back(), points.front(), point);
  for (int i = 0; i + 1 < points.size(); i++) {
    result_clockwise &= Clockwise(points[i], points[i + 1], point);
    result_counter_clockwise &= CounterClockwise(points[i], points[i + 1], point);
  }

  return (result_clockwise || result_counter_clockwise);
}

double GetPolarAngle(glm::vec2 a, glm::vec2 b) {
  if (a == b) {
    return 0;
  } else if (std::fabs(a.x - b.x) < kEps && a.y < b.y) {
    return 180.0;
  } else if (std::fabs(a.x - b.x) < kEps && a.y > b.y) {
    return 270.0;
  } else {
    double angle_radians = std::atan2(b.y - a.y, b.x - a.x),
        angle_degree = (angle_radians > 0 ? angle_radians : (2 * glm::pi<double>() + angle_radians)) * 360.0
        / (2.0 * glm::pi<double>());
    return angle_degree;
  }
}

