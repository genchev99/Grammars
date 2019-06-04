//
// Created by genchev99 on 26.05.19.
//

#include <iostream>
#include "Variable.h"


Variable::Variable(const Variable &other) {
//  std::cout << "Variable copy constructor" << std::endl;
  _value = other._value;
}

Variable::Variable(std::string variable) {
  _value = variable;
}

bool Variable::isTerminal() {
  return _value.at(0) >= 'a' && _value.at(0) <= 'z';
}

bool Variable::operator==(const Variable &rhs) const {
  return _value == rhs._value;
}

bool Variable::operator!=(const Variable &rhs) const {
  return !(rhs == *this);
}

bool Variable::operator<(const Variable &rhs) const {
  return _value < rhs._value;
}

bool Variable::operator>(const Variable &rhs) const {
  return rhs < *this;
}

bool Variable::operator<=(const Variable &rhs) const {
  return !(rhs < *this);
}

bool Variable::operator>=(const Variable &rhs) const {
  return !(*this < rhs);
}

bool Variable::isEpsilon() {
  return _value == "ε";
}

void Variable::setValue(std::string value) {
  _value = std::move(value);
}

Variable::~Variable() = default;

Variable::Variable() = default;
