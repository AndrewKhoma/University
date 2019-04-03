//
// Created by ahoma on 01/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include "ui/UI.h"

const int kWidth = 600;
const int kHeight = 400;

int main() {
  UI program(kWidth, kHeight, "Computational geometry");

  program.display();

  return 0;
}
