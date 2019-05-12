//
// Created by ahoma on 11/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include <UIImpl.h>

UIImpl::UIImpl(unsigned int width, unsigned int height, const std::string &program_name) : UI(width,
                                                                                              height,
                                                                                              program_name) {
  adding_data_ = true;
}

void UIImpl::DrawImGuiPanel() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("Bezier spline");

  ImGui::SetWindowPos(ImVec2(0, 0));
  ImGui::SetWindowSize(ImVec2(350, 150));

  if (adding_data_) {
    ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
  }

  auto button_add_points = ImGui::Button("Add point");

  if (adding_data_) {
    ImGui::PopItemFlag();
    ImGui::PopStyleVar();
  }

  if (!adding_data_) {
    ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
  }

  ImGui::SameLine();

  auto button_delete_points = ImGui::Button("Delete point");

  if (!adding_data_) {
    ImGui::PopItemFlag();
    ImGui::PopStyleVar();
  }

  if (button_add_points) {
    adding_data_ = true;
  } else if (button_delete_points) {
    adding_data_ = false;
  }

  auto load_variant = ImGui::Button("Load variant");
  if (load_variant) {
    Reset();
    input_points_ = {{1, 1}, {2, 2}, {3, 3}, {5, 3}, {7, 2}, {6, 1}, {8, 3}, {9, 1}, {10, 3}};
    for (int i = 0; i < input_points_.size(); i++) {
      point_labels_.emplace_back("point " + std::to_string(i));
      painter_.Add(new DrawableObject(input_points_[i], GL_POINTS, 5.f),
                   GLMColors::kBlackColor,
                   point_labels_.back());
    }
    painter_.Add(new DrawableObject(Algorithm::Bezier(input_points_), GL_LINE_STRIP, 3.0f),
                 GLMColors::kRedColor,
                 "bezier spline");
  }

  ImGui::SameLine();

  auto delete_all_points = ImGui::Button("Delete points");
  if (delete_all_points) {
    Reset();
  }

  manager_.Render();

  static glm::dvec2 cursor_pos;
  cursor_pos = GetCursorPosition();

  static int point_covered;
  point_covered = NumberOfCoveredPoints();

  // You can be the baddest badass, but please, stick to grammar
  if (point_covered != 1) {
    ImGui::Text("Currently you cover %d points", point_covered);
  } else {
    ImGui::Text("Currently you cover 1 point");
  }

  if (adding_data_) {
    ImGui::Text("Point (%.3f, %.3f) will be added", cursor_pos.x, cursor_pos.y);
  } else if (point_covered > 0) {
    static std::vector<glm::vec2>::const_iterator current_point;
    current_point = GetCoveredPoint();
    if (current_point != input_points_.end()) {
      ImGui::Text("Point (%.3f, %.3f) will be deleted", current_point->x, current_point->y);
    }
  }

  ImGui::Text("x: %.6f y: %.6f", cursor_pos.x, cursor_pos.y);

  ImGui::End();
}

void UIImpl::MouseButtonCallback(GLFWwindow *, int button, int action, int) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !ImGui::IsAnyWindowHovered()) {
    if (adding_data_) {
      static uint64_t curr_point_num = 0;
      glm::dvec2 cursor_position = GetCursorPosition();
      input_points_.emplace_back(cursor_position.x, cursor_position.y);
      point_labels_.emplace_back("point " + std::to_string(curr_point_num++));
      painter_.Add(new DrawableObject(glm::vec2(cursor_position), GL_POINTS, 5.f),
                   GLMColors::kBlackColor,
                   point_labels_.back());
      painter_.DeleteByName("bezier spline");
      painter_.Add(new DrawableObject(Algorithm::Bezier(input_points_), GL_LINE_STRIP, 3.0f),
                   GLMColors::kRedColor,
                   "bezier spline");
    } else {
      if (NumberOfCoveredPoints() > 0) {
        static std::vector<glm::vec2>::const_iterator point_to_delete;
        point_to_delete = GetCoveredPoint();
        if (point_to_delete != input_points_.end()) {
          static int index_num;
          index_num = static_cast<int>(point_to_delete - input_points_.begin());
          painter_.DeleteByName(point_labels_[index_num]);
          input_points_.erase(point_to_delete);
          point_labels_.erase(point_labels_.begin() + index_num);
          painter_.DeleteByName("bezier spline");
          painter_.Add(new DrawableObject(Algorithm::Bezier(input_points_), GL_LINE_STRIP, 3.0f),
                       GLMColors::kRedColor,
                       "bezier spline");
        }
      } else {
        manager_.Add("You don't cover any point", "Error message", ImVec2(300, 50));
      }
    }
  }
}

int UIImpl::NumberOfCoveredPoints() const {
  static glm::dvec2 cursor;
  static double cursor_error;

  cursor = GetCursorPosition();
  cursor_error = GetCursorError();

  static int covered_points_num;
  covered_points_num = 0;

  for (auto point : input_points_) {
    if (glm::distance(glm::dvec2(point), cursor) < cursor_error) {
      covered_points_num++;
    }
  }
  return covered_points_num;
}

std::vector<glm::vec2>::const_iterator UIImpl::GetCoveredPoint() const {
  static glm::dvec2 cursor;
  static double cur_distance;
  cursor = GetCursorPosition();
  cur_distance = GetCursorError();
  auto possible_point = input_points_.end();
  for (auto point = input_points_.begin(); point != input_points_.end(); ++point) {
    static double point_distance;
    point_distance = glm::distance(glm::dvec2(*point), cursor);
    if (point_distance < cur_distance) {
      cur_distance = point_distance;
      possible_point = point;
    }
  }

  return possible_point;
}

void UIImpl::Reset() {
  adding_data_ = true;
  input_points_.clear();
  while (!point_labels_.empty()) {
    painter_.DeleteByName(point_labels_.back());
    point_labels_.pop_back();
  }
  painter_.DeleteByName("bezier spline");
}
