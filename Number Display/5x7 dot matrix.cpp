//
//  5x7 dot matrix.cpp
//  Number Display
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "5x7 dot matrix.hpp"

#include <cmath>

using namespace Display::Dot5x7;

constexpr float PI2 = 6.28318530718f;

namespace {
  void pushColor(std::vector<float> &colors, const Color color) {
    colors.push_back(color.r);
    colors.push_back(color.g);
    colors.push_back(color.b);
    colors.push_back(color.a);
  }

  void drawCircle(
    Mesh &mesh,
    const float x,
    const float y,
    const float radius,
    const unsigned detail,
    const Color color
  ) {
    const unsigned centerIndex = static_cast<unsigned>(mesh.colors.size());
  
    pushColor(mesh.colors, color);
    mesh.verts.push_back(x);
    mesh.verts.push_back(y);
    
    for (unsigned i = 0; i != detail; i++) {
      //counter clockwise winding
      mesh.indicies.push_back(static_cast<unsigned>(mesh.colors.size()));
      pushColor(mesh.colors, color);
      mesh.indicies.push_back(static_cast<unsigned>(mesh.colors.size()));
      mesh.indicies.push_back(centerIndex);
      const float angle = static_cast<float>(i) / detail * PI2;
      mesh.verts.push_back(x + std::cos(angle) * radius);
      mesh.verts.push_back(y + std::sin(angle) * radius);
    }
  }
}

Mesh Display::Dot5x7::circles(
  const std::experimental::string_view str,
  const CircleConfig config
) {
  
}
