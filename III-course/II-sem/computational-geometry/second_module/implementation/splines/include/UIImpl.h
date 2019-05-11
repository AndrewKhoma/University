//
// Created by ahoma on 11/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#ifndef IMPLEMENTATION_LAB7_INCLUDE_UIIMPL_H_
#define IMPLEMENTATION_LAB7_INCLUDE_UIIMPL_H_

#include <string>
#include <vector>

#include "UI.h"
#include "Algorithm.h"
#include "ReportManager.h"

class UIImpl : public UI {
 public:
  UIImpl(unsigned int width, unsigned int height, const std::string &program_name);

 private:
  ReportManager manager_;

  std::vector<glm::vec2> input_points_;  // possible input data
  std::vector<std::string> point_labels_;  // redrawing optimization

  bool adding_data_;

  void Reset();

  void DrawImGuiPanel() override;

  void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) override;

  int NumberOfCoveredPoints() const;

  std::vector<glm::vec2>::const_iterator GetCoveredPoint() const;
};

#endif  // IMPLEMENTATION_LAB7_INCLUDE_UIIMPL_H_
