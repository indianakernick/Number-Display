//
//  5x7 dot matrix.hpp
//  Number Display
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef five_x_seven_dot_matrix_hpp
#define five_x_seven_dot_matrix_hpp

#include <cstdint>
#include <string>
#include <experimental/string_view>

namespace Display::Dot5x7 {
  /*
  FONT[0][0] is the top    row of space and
  FONT[0][6] is the bottom row of space
  
  The least significant bit of a row is the left  most pixel and
  the most  significant bit of a row is the right most pixel
  */

  const uint8_t FONT[95][7] = {
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, // (space)
    {0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00000, 0b00100}, // !
    {0b01010, 0b01010, 0b01010, 0b00000, 0b00000, 0b00000, 0b00000}, // "
    {0b01010, 0b01010, 0b11111, 0b01010, 0b11111, 0b01010, 0b01010}, // #
    {0b00100, 0b11110, 0b00101, 0b01110, 0b10100, 0b01111, 0b00100}, // $
    {0b00011, 0b10011, 0b01000, 0b00100, 0b00010, 0b11001, 0b11000}, // %
    {0b00110, 0b01001, 0b00101, 0b00010, 0b10101, 0b01001, 0b10110}, // &
    {0b00110, 0b00100, 0b00010, 0b00000, 0b00000, 0b00000, 0b00000}, // '
    {0b01000, 0b00100, 0b00010, 0b00010, 0b00010, 0b00100, 0b01000}, // (
    {0b00010, 0b00100, 0b01000, 0b01000, 0b01000, 0b00100, 0b00010}, // )
    {0b00000, 0b01010, 0b00100, 0b11111, 0b00100, 0b01010, 0b00000}, // *
    {0b00000, 0b00100, 0b00100, 0b11111, 0b00100, 0b00100, 0b00000}, // +
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00110, 0b00100}, // ,
    {0b00000, 0b00000, 0b00000, 0b11111, 0b00000, 0b00000, 0b00000}, // -
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00110, 0b00110}, // .
    {0b00000, 0b10000, 0b01000, 0b00100, 0b00010, 0b00001, 0b00000}, // /
    {0b01110, 0b10001, 0b11001, 0b10101, 0b10011, 0b10001, 0b01110}, // 0
    {0b00100, 0b00110, 0b00100, 0b00100, 0b00100, 0b00100, 0b01110}, // 1
    {0b01110, 0b10001, 0b10000, 0b01000, 0b00100, 0b00010, 0b11111}, // 2
    {0b11111, 0b01000, 0b00100, 0b01000, 0b10000, 0b10001, 0b01110}, // 3
    {0b01000, 0b01100, 0b01010, 0b01001, 0b11111, 0b01000, 0b01000}, // 4
    {0b11111, 0b00001, 0b01111, 0b10000, 0b10000, 0b10001, 0b01110}, // 5
    {0b01100, 0b00010, 0b00001, 0b01111, 0b10001, 0b10001, 0b01110}, // 6
    {0b11111, 0b10000, 0b01000, 0b00100, 0b00010, 0b00010, 0b00010}, // 7
    {0b01110, 0b10001, 0b10001, 0b01110, 0b10001, 0b10001, 0b01110}, // 8
    {0b01110, 0b10001, 0b10001, 0b11110, 0b10000, 0b01000, 0b00110}, // 9
    {0b00000, 0b00110, 0b00110, 0b00000, 0b00110, 0b00110, 0b00000}, // :
    {0b00000, 0b00110, 0b00110, 0b00000, 0b00110, 0b00100, 0b00010}, // ;
    {0b10000, 0b01000, 0b00100, 0b00010, 0b00100, 0b01000, 0b10000}, // <
    {0b00000, 0b00000, 0b11111, 0b00000, 0b11111, 0b00000, 0b00000}, // =
    {0b00001, 0b00010, 0b00100, 0b01000, 0b00100, 0b00010, 0b00001}, // >
    {0b01110, 0b10001, 0b10000, 0b01000, 0b00100, 0b00000, 0b00100}, // ?
    {0b01110, 0b10001, 0b10000, 0b10110, 0b10101, 0b10101, 0b01110}, // @
    {0b01110, 0b10001, 0b10001, 0b10001, 0b11111, 0b10001, 0b10001}, // A
    {0b01111, 0b10001, 0b10001, 0b01111, 0b10001, 0b10001, 0b01111}, // B
    {0b01110, 0b10001, 0b00001, 0b00001, 0b00001, 0b10001, 0b01110}, // C
    {0b00111, 0b01001, 0b10001, 0b10001, 0b10001, 0b01001, 0b00111}, // D
    {0b11111, 0b00001, 0b00001, 0b01111, 0b00001, 0b00001, 0b11111}, // E
    {0b11111, 0b00001, 0b00001, 0b00111, 0b00001, 0b00001, 0b00001}, // F
    {0b01110, 0b10001, 0b00001, 0b00001, 0b11001, 0b10001, 0b01110}, // G
    {0b10001, 0b10001, 0b10001, 0b11111, 0b10001, 0b10001, 0b10001}, // H
    {0b01110, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b01110}, // I
    {0b11100, 0b01000, 0b01000, 0b01000, 0b01000, 0b01001, 0b00110}, // J
    {0b10001, 0b01001, 0b00101, 0b00011, 0b00101, 0b01001, 0b10001}, // K
    {0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b11111}, // L
    {0b10001, 0b11011, 0b10101, 0b10001, 0b10001, 0b10001, 0b10001}, // M
    {0b10001, 0b10001, 0b10011, 0b10101, 0b11001, 0b10001, 0b10001}, // N
    {0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110}, // O
    {0b01111, 0b10001, 0b10001, 0b01111, 0b00001, 0b00001, 0b00001}, // P
    {0b01110, 0b10001, 0b10001, 0b10001, 0b10101, 0b01001, 0b10110}, // Q
    {0b01111, 0b10001, 0b10001, 0b01111, 0b00101, 0b01001, 0b10001}, // R
    {0b11110, 0b00001, 0b00001, 0b01110, 0b10000, 0b10000, 0b01111}, // S
    {0b11111, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100}, // T
    {0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110}, // U
    {0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01010, 0b00100}, // V
    {0b10001, 0b10001, 0b10001, 0b10101, 0b10101, 0b11011, 0b10001}, // W
    {0b10001, 0b10001, 0b01010, 0b00100, 0b01010, 0b10001, 0b10001}, // X
    {0b10001, 0b10001, 0b01010, 0b00100, 0b00100, 0b00100, 0b00100}, // Y
    {0b11111, 0b10000, 0b01000, 0b00100, 0b00010, 0b00001, 0b11111}, // Z
    {0b11100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b11100}, // [
    {0b00000, 0b00001, 0b00010, 0b00100, 0b01000, 0b10000, 0b00000}, /* \ */
    {0b00111, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00111}, // ]
    {0b00100, 0b01010, 0b10001, 0b00000, 0b00000, 0b00000, 0b00000}, // ^
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111}, // _
    {0b00010, 0b00100, 0b01000, 0b00000, 0b00000, 0b00000, 0b00000}, // `
    {0b00000, 0b00000, 0b01110, 0b10000, 0b11110, 0b10001, 0b11110}, // a
    {0b00001, 0b00001, 0b01111, 0b10001, 0b10001, 0b10001, 0b01111}, // b
    {0b00000, 0b00000, 0b01110, 0b10001, 0b00001, 0b10001, 0b01110}, // c
    {0b10000, 0b10000, 0b11110, 0b10001, 0b10001, 0b10001, 0b11110}, // d
    {0b00000, 0b00000, 0b01110, 0b10001, 0b11111, 0b00001, 0b01110}, // e
    {0b01100, 0b10010, 0b00010, 0b00111, 0b00010, 0b00010, 0b00010}, // f
    {0b00000, 0b00000, 0b11110, 0b10001, 0b10001, 0b11110, 0b10000}, // g
    {0b00001, 0b00001, 0b01101, 0b10011, 0b10001, 0b10001, 0b10001}, // h
    {0b00100, 0b00000, 0b00110, 0b00100, 0b00100, 0b00100, 0b01110}, // i
    {0b01000, 0b00000, 0b01100, 0b01000, 0b01000, 0b01000, 0b01001}, // j
    {0b00010, 0b00010, 0b10010, 0b01010, 0b00110, 0b01010, 0b10010}, // k
    {0b00110, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b01110}, // l
    {0b00000, 0b00000, 0b01011, 0b10101, 0b10101, 0b10001, 0b10001}, // m
    {0b00000, 0b00000, 0b01101, 0b10011, 0b10001, 0b10001, 0b10001}, // n
    {0b00000, 0b00000, 0b01110, 0b10001, 0b10001, 0b10001, 0b01110}, // o
    {0b00000, 0b00000, 0b01111, 0b10001, 0b10001, 0b01111, 0b00001}, // p
    {0b00000, 0b00000, 0b11110, 0b10001, 0b10001, 0b11110, 0b10000}, // q
    {0b00000, 0b00000, 0b01101, 0b10011, 0b00001, 0b00001, 0b00001}, // r
    {0b00000, 0b00000, 0b01110, 0b00001, 0b01110, 0b10000, 0b01111}, // s
    {0b00010, 0b00010, 0b00111, 0b00010, 0b00010, 0b10010, 0b01100}, // t
    {0b00000, 0b00000, 0b10001, 0b10001, 0b10001, 0b11001, 0b10110}, // u
    {0b00000, 0b00000, 0b10001, 0b10001, 0b10001, 0b01010, 0b00100}, // v
    {0b00000, 0b00000, 0b10001, 0b10001, 0b10101, 0b10101, 0b01010}, // w
    {0b00000, 0b00000, 0b10001, 0b01010, 0b00100, 0b01010, 0b10001}, // x
    {0b00000, 0b00000, 0b10001, 0b10001, 0b10001, 0b11110, 0b10000}, // y
    {0b00000, 0b00000, 0b11111, 0b01000, 0b00100, 0b00010, 0b11111}, // z
    {0b01000, 0b00100, 0b00100, 0b00010, 0b00100, 0b00100, 0b01000}, // {
    {0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100}, // |
    {0b00010, 0b00100, 0b00100, 0b01000, 0b00100, 0b00100, 0b00010}, // }
    {0b10010, 0b10101, 0b01001, 0b00000, 0b00000, 0b00000, 0b00000}, // ~
  };
};

#endif