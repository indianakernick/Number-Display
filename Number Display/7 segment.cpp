//
//  7 segment.cpp
//  Number Display
//
//  Created by Indi Kernick on 24/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "7 segment.hpp"

namespace {
  bool validChar(const char c) {
    return ('0' <= c && c <= '9') ||
           ('A' <= c && c <= 'F');
  }

  size_t charToIndex(const char c) {
    if ('0' <= c && c <= '9') {
      return c - '0';
    } else {
      return c - 'A' + 10;
    }
  }

  void checkChars(const std::experimental::string_view str) {
    for (auto c = str.begin(); c != str.end(); ++c) {
      if (!validChar(*c)) {
        throw Display::InvalidChar(*c);
      }
    }
  }
  
  struct Metrics {
    size_t digitWidth;
    size_t digitHeight;
    //the x position of segments B and C
    size_t rightSegPos;
    //the y position of segment G
    size_t middleSegPos;
    //the y position of segment D
    size_t bottomSegPos;
    size_t charWidth;
  };
  
  Metrics calcMetrics(
    const size_t numChars,
    const size_t horiSegLength,
    const size_t vertSegLength,
    const size_t distBetween
  ) {
    Metrics metrics;
    
    metrics.digitWidth = horiSegLength + 2 + distBetween;
    metrics.digitHeight = 2 * vertSegLength + 3;
    metrics.rightSegPos = horiSegLength + 1;
    metrics.middleSegPos = vertSegLength + 1;
    metrics.bottomSegPos = vertSegLength * 2 + 2;
    metrics.charWidth = metrics.digitWidth * numChars - distBetween + 1;
    
    return metrics;
  }
  
  bool getSegState(const size_t charIndex, const Display::Seg7::Segment seg) {
    return Display::Seg7::DIGIT_TO_SEG[charIndex][static_cast<size_t>(seg)];
  }
}


std::string Display::Seg7::ascii(
  const std::experimental::string_view digits,
  const size_t horiSegLength,
  const size_t vertSegLength,
  const size_t distBetween
) {
  checkChars(digits);
  
  const Metrics m = calcMetrics(digits.size(), horiSegLength, vertSegLength, distBetween);
  
  const char horiChar = '-';
  const char vertChar = '|';
  
  std::string out(m.charWidth * m.digitHeight, ' ');
  
  for (size_t i = 1; i <= m.digitHeight; ++i) {
    out[i * m.charWidth] = '\n';
  }
  
  for (size_t d = 0; d != digits.size(); ++d) {
    const size_t charIndex = charToIndex(digits[d]);
    const size_t posX = charIndex * m.digitWidth;
    
    for (size_t h = 1; h <= horiSegLength; ++h) {
      if (getSegState(charIndex, Segment::A)) {
        out[posX + h] = horiChar;
      }
      if (getSegState(charIndex, Segment::G)) {
        out[m.middleSegPos * m.charWidth + posX + h] = horiChar;
      }
      if (getSegState(charIndex, Segment::D)) {
        out[m.bottomSegPos * m.charWidth + posX + h] = horiChar;
      }
    }
    
    for (size_t v = 1; v <= vertSegLength; ++v) {
      if (getSegState(charIndex, Segment::F)) {
        out[v * m.charWidth] = vertChar;
      }
      if (getSegState(charIndex, Segment::E)) {
        out[(v + m.middleSegPos) * m.charWidth] = vertChar;
      }
      if (getSegState(charIndex, Segment::B)) {
        out[v * m.charWidth + m.rightSegPos] = vertChar;
      }
      if (getSegState(charIndex, Segment::C)) {
        out[(v + m.middleSegPos) * m.charWidth + m.rightSegPos] = vertChar;
      }
    }
  }
  
  return out;
}
