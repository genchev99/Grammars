#include <utility>
#include <iostream>

//
// Created by genchev99 on 26.05.19.
//

#include "Rule.h"
#include "Terminal.h"

Rule::Rule() = default;

Rule::Rule(long id, std::string left, std::string right) {
  _id = id;
  _left = NonTerminal(std::move(left));
  for (unsigned long i = 0; i < right.size(); ++i) {
    if (std::islower(right.at(i))) {
      _right.push_back(new Terminal(std::string(1, right.at(i))));
    } else if (std::isupper(right.at(i))) {
      unsigned long numbers = i+1;
      while (numbers < right.size() && std::isdigit(right.at(numbers))) {
        numbers++;
      }
      _right.push_back(new NonTerminal(right.substr(i, numbers - i)));
      i = numbers -1;
    }
  }
}

void Rule::print() {
  std::cout << "[ * ] ID: " << _id << " " << _left.getValue() << " -> ";
  for (const auto &right : _right) {
    std::cout << right->getValue();
  }
  std::cout << std::endl;
}

void Rule::modify(long id) {
  _left.addIndex(id);
  for (const auto &right : _right) {
    right->addIndex(id);
  }
}

Rule::Rule(const Rule &other) {
  _id = other._id;
  _left = NonTerminal(other._left);
  for (const auto &right : other._right) {
    if (right->isTerminal()) {
      _right.push_back(new Terminal(right->getValue())); /* Dont know how to call the copy constructor */
    } else {
      _right.push_back(new NonTerminal(right->getValue())); /* Dont know how to call the copy constructor */
    }
  }
}

long Rule::get_id() {
  return _id;
}

std::string Rule::getLeftValue() {
  return _left.getValue();
}

std::string Rule::getRightValue() {
  std::string right;
  for (auto &part : _right) {
    right += part->getValue();
  }

  return right;
}

bool Rule::isChomsky() {
  if (_right.size() > 2) return false; /* More than 2 rules on the right side */

  if (_right.size() == 1) {
    if (!_right.at(0)->isTerminal()) return false; /* Single non terminal rule */
    if (_right.at(0)->isEpsilon()) return false; /* Epsilon rule */
  }

  if (_right.size() == 2) {
    if (_right.at(0)->isTerminal() || _right.at(1)->isTerminal()) return false; /* Not 2 non terminals on the right side */
  }

  return true;
}
