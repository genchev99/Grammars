//
// Created by genchev99 on 26.05.19.
//

#include <iostream>
#include "Terminal.h"

Terminal::Terminal() = default;
Terminal::Terminal(const Variable &other): Variable(other) {}
Terminal::Terminal(const Terminal &other): Variable(other) {
//  std::cout << "Terminal copy constructor" << std::endl;
  _value = other._value;
}

Terminal::Terminal(std::string terminal): Variable(terminal) {}

std::string Terminal::getValue() {
  return _value;
}

void Terminal::addIndex(long id) {}

Terminal::~Terminal() {

}
/* Noting happens */
