//
// Created by ahoma on 11/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include <UIImpl.h>

UIImpl::UIImpl(unsigned int width, unsigned int height, const std::string &program_name) : UI(width,
                                                                                              height,
                                                                                              program_name,
                                                                                              3) {
  adding_data_ = true;
}

void UIImpl::DrawImGuiPanel() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("NURBS surface");

  ImGui::SetWindowPos(ImVec2(0, 0));
  ImGui::SetWindowSize(ImVec2(350, 100));

  auto load_variant = ImGui::Button("Load variant");

  static int u_point_num = 5, v_point_num = 5;

  if (load_variant) {
    Reset();
    Draw(u_point_num, v_point_num);
  }

  ImGui::SameLine();

  auto delete_all_points = ImGui::Button("Reset");
  if (delete_all_points) {
    Reset();
  }

  static int previous_u = 0, previous_v = 0;

  ImGui::InputInt("U detailing", &u_point_num);

  if (u_point_num <= 0) {
    manager_.Add("U-parameter point number should\nbe positive", "Error message", ImVec2(200, 75));
    u_point_num = 1;
  }

  ImGui::InputInt("V detailing", &v_point_num);

  if (v_point_num <= 0) {
    manager_.Add("V-parameter point number should\nbe positive", "Error message", ImVec2(200, 75));
    v_point_num = 1;
  }

  if (!input_points_.empty() && (previous_u != u_point_num || previous_v != v_point_num)) {
    Reset();
    Draw(u_point_num, v_point_num);
  }

  previous_v = v_point_num, previous_u = u_point_num;
  manager_.Render();
  ImGui::End();
}

void UIImpl::MouseButtonCallback(GLFWwindow *, int, int, int) {

}

void UIImpl::Draw(int u_point_num, int v_point_num) {
  input_points_ = {{1, 1, 4}, {2, 3, 4}, {3, 2, 4}, {4, 4, 0}, {5, 1, 1}, {6, 5, 2}, {7, 3, 3}, {9, 1, 4}};
  for (auto input_point : input_points_) {
    painter_.Add(new DrawableObject3D(input_point, GL_POINTS, 5.f),
                 GLMColors::kBlackColor,
                 "input points");
  }
  tinynurbs::RationalSurface3f surf = Algorithm::NURBSSurface(input_points_);
  auto points = Algorithm::NURBSPoints(surf, u_point_num, v_point_num);
  for (const auto &spline: points) {
    painter_.Add(new DrawableObject3D(spline, GL_LINE_STRIP, 2.5f), GLMColors::kGreenColor, "NURBS surface");
  }
}

void UIImpl::Reset() {
  adding_data_ = true;
  input_points_.clear();
  painter_.DeleteByName("input points");
  painter_.DeleteByName("NURBS surface");
}

