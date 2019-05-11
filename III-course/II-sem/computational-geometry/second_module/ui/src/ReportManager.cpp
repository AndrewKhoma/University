// Copyright (c) 2019.
// Created by Andrii Khoma on 11/04/19.
// All rights reserved.

#include "ReportManager.h"

void ReportManager::Add(const std::string &message, const std::string &window_name, ImVec2 window_size) {
  message_ = message;
  window_name_ = window_name;
  window_size_ = window_size;
}

void ReportManager::Render() {
  if (!message_.empty()) {
    ImGui::OpenPopup(window_name_.c_str());
  }

  bool open = true;
  if (ImGui::BeginPopupModal(window_name_.c_str(), &open)) {
    ImGui::SetWindowPos(ImVec2((ImGui::GetIO().DisplaySize.x - window_size_.x) * 0.5f,
                               (ImGui::GetIO().DisplaySize.y - window_size_.y) * 0.5f),
                        ImGuiCond_Always);
    ImGui::SetWindowSize(window_size_);
    ImGui::Text(message_.c_str(), nullptr);
    ImGui::EndPopup();
  }

  if (!open) {
    message_ = "";
  }
}
