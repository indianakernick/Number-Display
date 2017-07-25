//
//  7 segment.cpp
//  Number Display
//
//  Created by Indi Kernick on 24/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "7 segment.hpp"

#include <cassert>
#include <codecvt>

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
  
  wchar_t corner(
    const bool top,
    const bool right,
    const bool bottom,
    const bool left
  ) {
    const uint8_t bits = (top << 3) | (right << 2) | (bottom << 1) | left;
    
    switch (bits) {
      case 0b0000:
        return L' ';
      case 0b0001:
        return L'╴';
      case 0b0010:
        return L'╷';
      case 0b0011:
        return L'┐';
      case 0b0100:
        return L'╶';
      case 0b0101:
        return L'─';
      case 0b0110:
        return L'┌';
      case 0b0111:
        return L'┬';
      case 0b1000:
        return L'╵';
      case 0b1001:
        return L'┘';
      case 0b1010:
        return L'│';
      case 0b1011:
        return L'┤';
      case 0b1100:
        return L'└';
      case 0b1101:
        return L'┴';
      case 0b1110:
        return L'├';
      case 0b1111:
        return L'┼';
      
      default:
        assert(false);
        return L' ';
    }
  }
  
  struct GetSegState {
    explicit GetSegState(const size_t charIndex)
      : charIndex(charIndex) {}
    
    bool operator()(const Display::Seg7::Segment seg) {
      return Display::Seg7::DIGIT_TO_SEG[charIndex][static_cast<size_t>(seg)];
    }
    
  private:
    size_t charIndex;
  };
  
  template <typename Char>
  struct SetChar {
    SetChar(std::basic_string<Char> &str, const size_t posX, const size_t charWidth)
      : str(str), posX(posX), charWidth(charWidth) {}
    
    void operator()(const size_t x, const size_t y, const Char c) {
      str[y * charWidth + posX + x] = c;
    }
    
  private:
    std::basic_string<Char> &str;
    const size_t posX;
    const size_t charWidth;
  };
  
  template <typename Char>
  std::basic_string<Char> charDisplayImpl(
    const std::experimental::string_view digits,
    const size_t horiSegLength,
    const size_t vertSegLength,
    const size_t distBetween,
    const Char horiChar,
    const Char vertChar
  ) {
    using namespace Display::Seg7;
  
    checkChars(digits);
  
    const Metrics m = calcMetrics(
      digits.size(),
      horiSegLength,
      vertSegLength,
      distBetween
    );
    
    std::basic_string<Char> out(m.charWidth * m.digitHeight, Char(' '));
    
    for (size_t i = 1; i <= m.digitHeight; ++i) {
      out[i * m.charWidth - 1] = Char('\n');
    }
    
    for (size_t d = 0; d != digits.size(); ++d) {
      GetSegState getSegState(charToIndex(digits[d]));
      SetChar<Char> setChar(out, d * m.digitWidth, m.charWidth);
      
      //horizontal segments (A, G, D)
      for (size_t h = 1; h <= horiSegLength; ++h) {
        if (getSegState(Segment::A)) {
          setChar(h, 0, horiChar);
        }
        if (getSegState(Segment::G)) {
          setChar(h, m.middleSegPos, horiChar);
        }
        if (getSegState(Segment::D)) {
          setChar(h, m.bottomSegPos, horiChar);
        }
      }
      
      //vertical segments (F, E, B, C)
      for (size_t v = 1; v <= vertSegLength; ++v) {
        if (getSegState(Segment::F)) {
          setChar(0, v, vertChar);
        }
        if (getSegState(Segment::E)) {
          setChar(0, v + m.middleSegPos, vertChar);
        }
        if (getSegState(Segment::B)) {
          setChar(m.rightSegPos, v, vertChar);
        }
        if (getSegState(Segment::C)) {
          setChar(m.rightSegPos, v + m.middleSegPos, vertChar);
        }
      }
    }
    
    return out;
  }
}


std::string Display::Seg7::ascii(
  const std::experimental::string_view digits,
  const size_t horiSegLength,
  const size_t vertSegLength,
  const size_t distBetween
) {
  return charDisplayImpl(
    digits,
    horiSegLength,
    vertSegLength,
    distBetween,
    '-',
    '!'
  );
}

std::string Display::Seg7::unicode(
  const std::experimental::string_view digits,
  const size_t horiSegLength,
  const size_t vertSegLength,
  const size_t distBetween
) {
  std::wstring out = charDisplayImpl(
    digits,
    horiSegLength,
    vertSegLength,
    distBetween,
    L'─',
    L'│'
  );
  
  const Metrics m = calcMetrics(
    digits.size(),
    horiSegLength,
    vertSegLength,
    distBetween
  );
  
  for (size_t d = 0; d != digits.size(); ++d) {
    GetSegState getSeg(charToIndex(digits[d]));
    SetChar<wchar_t> setChar(out, d * m.digitWidth, m.charWidth);
    
    #define GET_SEG(SEG) (Segment::SEG == Segment::NONE ? false : getSeg(Segment::SEG))
    #define CORNER(TOP, RIGHT, BOTTOM, LEFT) corner(GET_SEG(TOP), GET_SEG(RIGHT), GET_SEG(BOTTOM), GET_SEG(LEFT))
    
    setChar(0,             0,              CORNER(NONE, A,    F,    NONE));
    setChar(m.rightSegPos, 0,              CORNER(NONE, NONE, B,    A   ));
    setChar(0,             m.middleSegPos, CORNER(F,    G,    E,    NONE));
    setChar(m.rightSegPos, m.middleSegPos, CORNER(B,    NONE, C,    G   ));
    setChar(0,             m.bottomSegPos, CORNER(E,    D,    NONE, NONE));
    setChar(m.rightSegPos, m.bottomSegPos, CORNER(C,    NONE, NONE, D   ));
    
    #undef CORNER
    #undef GET_SEG
  }
  
  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  return converter.to_bytes(out);
}
