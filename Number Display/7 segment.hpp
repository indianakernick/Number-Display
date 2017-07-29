//
//  7 segment.hpp
//  Number Display
//
//  Created by Indi Kernick on 24/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef number_display_seven_segment_hpp
#define number_display_seven_segment_hpp

#include <string>
#include "invalid char.hpp"
#include <experimental/string_view>

namespace Display::Seg7 {
  /*
   --A--
  |     |
  F     B
  |     |
   --G--
  |     |
  E     C
  |     |
   --D--

  byte encoding

  0abcdefg

  chars
  0 1 2 3 4 5 6 7 8 9 A b C d E F
  */

  enum class Segment {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    
    NONE
  };

  const bool DIGIT_TO_SEG[16][7] = {
  // a b c d e f g
    {1,1,1,1,1,1,0},//0
    {0,1,1,0,0,0,0},//1
    {1,1,0,1,1,0,1},//2
    {1,1,1,1,0,0,1},//3
    {0,1,1,0,0,1,1},//4
    {1,0,1,1,0,1,1},//5
    {1,0,1,1,1,1,1},//6
    {1,1,1,0,0,0,0},//7
    {1,1,1,1,1,1,1},//8
    {1,1,1,1,0,1,1},//9
    {1,1,1,0,1,1,1},//A
    {0,0,1,1,1,1,1},//b
    {1,0,0,1,1,1,0},//C
    {0,1,1,1,1,0,1},//d
    {1,0,0,1,1,1,1},//E
    {1,0,0,0,1,1,1} //F
  };
  
  std::string ascii(std::experimental::string_view, size_t, size_t, size_t);
  std::string unicode(std::experimental::string_view, size_t, size_t, size_t);
}

#endif
