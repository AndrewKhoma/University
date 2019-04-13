//
// Created by ahoma on 01/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include "UI.h"

const int kWidth = 800;
const int kHeight = 600;

int main() {
  UI program(kWidth, kHeight, "Computational geometry");

  std::vector<glm::vec2>
      points{glm::vec2(1.0f, -1.0f), glm::vec2(-1.0f, -1.0f), glm::vec2(-1.0f, 1.0f), glm::vec2(1.0f, 1.0f)};

  program.display(points);

  return 0;
}
