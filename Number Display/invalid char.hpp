//
//  invalid char.hpp
//  Number Display
//
//  Created by Indi Kernick on 24/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef number_display_invalid_char_hpp
#define number_display_invalid_char_hpp

#include <exception>

namespace Display {
  class InvalidChar : public std::exception {
  public:
    explicit InvalidChar(char);
    
    char getChar() const;
    
    virtual const char *what() const noexcept override;
  
  private:
    char c;
  };
}

#endif
