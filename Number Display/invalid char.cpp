//
//  invalid char.cpp
//  Number Display
//
//  Created by Indi Kernick on 24/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "invalid char.hpp"

Display::InvalidChar::InvalidChar(const char c)
  : c(c) {}

char Display::InvalidChar::getChar() const {
  return c;
}

const char *Display::InvalidChar::what() const noexcept {
  return "Character cannot be displayed";
}
