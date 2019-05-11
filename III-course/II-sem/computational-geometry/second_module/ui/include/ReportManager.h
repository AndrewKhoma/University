// Copyright (c) 2019.
// Created by Andrii Khoma on 11/04/19.
// All rights reserved.

#ifndef UI_INCLUDE_REPORTMANAGER_H_
#define UI_INCLUDE_REPORTMANAGER_H_

#include <imgui.h>

#include <string>

class ReportManager {
 public:
  void Add(const std::string &message, const std::string &window_name, ImVec2 window_size);

  void Render();
 private:
  std::string message_, window_name_;
  ImVec2 window_size_;
};

#endif  // UI_INCLUDE_REPORTMANAGER_H_
