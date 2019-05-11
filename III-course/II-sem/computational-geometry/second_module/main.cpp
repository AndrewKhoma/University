//
// Created by ahoma on 01/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include "UI.h"
#include "UIImpl.h"

const int kWidth = 800;
const int kHeight = 600;

int main() {
  UI *program = new UIImpl(kWidth, kHeight, "Computational geometry");

  program->display(glm::vec2{-1, -1}, glm::vec2{11, 4});

  delete program;

  return 0;
}
