/*
 *  Number_Display.cpp
 *  Number Display
 *
 *  Created by Indi Kernick on 24/7/17.
 *  Copyright © 2017 Indi Kernick. All rights reserved.
 *
 */

#include <iostream>
#include "Number_Display.hpp"
#include "Number_DisplayPriv.hpp"

void Number_Display::HelloWorld(const char * s)
{
    Number_DisplayPriv *theObj = new Number_DisplayPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void Number_DisplayPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

