//
// Created by genchev99 on 26.05.19.
//

#include <iostream>
#include "NonTerminal.h"

std::string NonTerminal::getValue() {
  return _value + getIndexAsString();
}

std::string NonTerminal::getIndexAsString() {
  std::string result;
  for (const auto &index : _indexes) {
    result += std::to_string(index);
  }

  return result;
}

NonTerminal::NonTerminal(std::string nonTerminal): Variable() {
  for (auto &character : nonTerminal) {
    if (std::isupper(character)) {
      _value += character;
    } else if (std::isdigit(character)) {
      _indexes.push_back(character - '0');
    }
  }
}

NonTerminal::NonTerminal(const NonTerminal &other) {
//  std::cout << "Non-Terminal copy constructor" << std::endl;
  _value = other._value;
  _indexes = other._indexes;
}

void NonTerminal::addIndex(long id) {
  _indexes.push_back(id);
}

void NonTerminal::Destroy() {
  delete(this);
}

//NonTerminal::~NonTerminal() = default;

NonTerminal::NonTerminal() = default;
