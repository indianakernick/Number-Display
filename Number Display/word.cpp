//
//  word.cpp
//  Number Display
//
//  Created by Indi Kernick on 25/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "word.hpp"

#include <unordered_map>

namespace {
  const std::unordered_map<int64_t, const char *> numNames = {
    {-1, "negative"},
    {0, "zero"},
    {1, "one"},
    {2, "two"},
    {3, "three"},
    {4, "four"},
    {5, "five"},
    {6, "six"},
    {7, "seven"},
    {8, "eight"},
    {9, "nine"},
    {10, "ten"},
    {11, "eleven"},
    {12, "twelve"},
    {13, "thirteen"},
    {14, "fourteen"},
    {15, "fifteen"},
    {16, "sixteen"},
    {17, "seventeen"},
    {18, "eighteen"},
    {19, "nineteen"},
    {20, "twenty"},
    {30, "thirty"},
    {40, "fourty"},
    {50, "fifty"},
    {60, "sixty"},
    {70, "seventy"},
    {80, "eighty"},
    {90, "ninety"},
    {100, "hundred"},
    {1000, "thousand"},
    {1000000, "million"},
    {1000000000, "billion"},
    {1000000000000, "trillion"},
    {1000000000000000, "quadrillion"},
    {1000000000000000000, "quintillion"},
  };
  
  std::string threeDigits(const uint8_t h, const uint8_t t, const uint8_t o) {
    if (h == 0 && t == 0 && o == 0) {
      return numNames.at(0);
    }
    
    std::string out;
    
    if (h) {
      out += numNames.at(h);
      out += " ";
      out += numNames.at(100);
      if (t || o) {
        out += " and ";
      }
    }
    
    if (t == 1) {
      out += numNames.at(10 + o);
    } else {
      if (t) {
        out += numNames.at(t * 10);
        if (o) {
          out += " ";
        }
      }
      if (o) {
        out += numNames.at(o);
      }
    }
    
    return out;
  }
}

std::string Display::Word::number(int64_t num) {
  //Before I started writing this, I knew it would be messy!


  constexpr size_t NUM_DIGITS = 21;//should be a multiple of 3
  constexpr size_t NUM_SECTIONS = NUM_DIGITS / 3;
  
  uint8_t digits[NUM_DIGITS];
  bool nonZeroSections[NUM_SECTIONS] = {};
  std::string out;
  
  if (num < 0) {
    num = -num;
    out = numNames.at(-1);
    out += " ";
  } else if (num == 0) {
    return numNames.at(0);
  }
  
  for (size_t d = NUM_DIGITS - 1; d != -size_t(1); --d) {
    digits[d] = num % 10;
    num /= 10;
    if (digits[d]) {
      nonZeroSections[d / 3] = true;
    }
  }
  
  for (size_t s = 0; s != NUM_SECTIONS; ++s) {
    if (nonZeroSections[s]) {
      out += threeDigits(digits[s * 3], digits[s * 3 + 1], digits[s * 3 + 2]);
      if (s != NUM_SECTIONS - 1) {
        out += " ";
        out += numNames.at(std::pow(10, (NUM_SECTIONS - s - 1) * 3));
        
        size_t numNextNonZeroSections = 0;
        size_t nextNonZeroSection = 0;
        for (size_t n = s + 1; n != NUM_SECTIONS; ++n) {
          if (nonZeroSections[n]) {
            numNextNonZeroSections++;
            nextNonZeroSection = n;
          }
        }
        //if the next non-zero section has a hundreds value then use a ", "
        if (numNextNonZeroSections == 1 && digits[nextNonZeroSection * 3] == 0) {
          out += " and ";
        } else if (numNextNonZeroSections != 0) {
          out += ", ";
        }
      }
    }
  }
  
  return out;
}
