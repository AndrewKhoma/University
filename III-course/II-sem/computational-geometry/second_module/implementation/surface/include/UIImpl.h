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

  std::vector<glm::vec3> input_points_;  // possible input data

  bool adding_data_;

  void Draw(int u_point_num, int v_point_num);

  void Reset();

  void DrawImGuiPanel() override;

  void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) override;
};

#endif  // IMPLEMENTATION_LAB7_INCLUDE_UIIMPL_H_
