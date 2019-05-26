//
// Created by genchev99 on 26.05.19.
//

#include <iostream>
#include <algorithm>
#include "Grammar.h"
#include "StringManager.h"

Grammar::Grammar() {
  _nextRuleId = 0;
};

Grammar::Grammar(long id, std::string grammar) {
  _id = id;
  grammar = StringManager(grammar).eraseFromString(" (){}");
//  grammar = (new StringManager(grammar))->eraseFromString(" (){}");
  std::vector<std::string> sets = StringManager(grammar).splitBy(';');
//  std::vector<std::string> sets = (new StringManager(grammar))->splitBy(';');

  /* at 0 - NonTerminals */
  /* at 1 - Terminals */
  /* at 2 - Start NonTerminal */
  /* at 2 - Rules */

  /* In case the line is not in correct form */
  /* TODO If strict mode terminate process */
  if (sets.size() != 4) {
    std::cerr << "incompatible grammar" << std::endl;
    exit(1);
  }
  for (auto rawTerminal: StringManager(sets.at(1)).splitBy(',')) {
    _terminals.push_back(Terminal(rawTerminal));
  }
  for (auto rawNonTerminal: StringManager(sets.at(0)).splitBy(',')) {
    _nonTerminals.push_back(NonTerminal(rawNonTerminal));
  }
  _start = NonTerminal(sets.at(2));
  _nextRuleId = 0;


  std::vector<std::string> rulesSets = StringManager(sets.at(3)).splitBy(',');
  for (auto &rule : rulesSets) {
    std::vector<std::string> splitRule = StringManager(rule).splitBy('>');
    if (splitRule.size() != 2) {
      std::cerr << "incompatible rule size" << std::endl;
      exit(1);
    }
    std::vector<std::string> splitRight = StringManager(splitRule.at(1)).splitBy('|');
    if (splitRight.empty()) {
      std::cerr << "incompatible rule right" << std::endl;
      exit(1);
    }
    for (const auto &item : splitRight) {
      _rules.push_back(Rule(++_nextRuleId, splitRule.at(0), item));
    }
  }
}

Grammar::Grammar(const Grammar &other) {
//  std::cout << "Grammar copy constructor" << std::endl;
  _id = other._id;
  _nextRuleId = other._nextRuleId;
  _nonTerminals = other._nonTerminals;
  _terminals = other._terminals;
  _start = other._start;
  _rules = other._rules;
}

template <typename T>
void printSet(std::vector<T> elements) {
  unsigned long setLength = elements.size();
  for (unsigned long i = 0; i < setLength; ++i) {
    std::cout << elements.at(i).getValue();
    if (i != setLength - 1) {
      std::cout << ", ";
    }
  }

  std::cout << std::endl;
}

void Grammar::print() {
  std::cout << "[ * ] Grammar ID: " << _id << std::endl;
  std::cout << "[ * ] Start: " << _start.getValue() << std::endl;
  std::cout << "[ * ] Terminals: ";
  printSet<Terminal>(_terminals);
  std::cout << "[ * ] Non-Terminals: ";
  printSet<NonTerminal>(_nonTerminals);
  std::cout << "[ * ] Rules: " << std::endl;
  for (auto &rule : _rules) {
    rule.print();
  }
  std::cout << std::endl;
}

/* Union */
Grammar Grammar::operator+(const Grammar &other) {
  Grammar thisCopy(*this);
  Grammar otherCopy(other);
  Grammar result;

  thisCopy.modify(thisCopy._id);
  otherCopy.modify(otherCopy._id);

  result._nonTerminals = thisCopy._nonTerminals;
  result._nonTerminals.insert(result._nonTerminals.end(), otherCopy._nonTerminals.begin(), otherCopy._nonTerminals.end());

  result._terminals = thisCopy._terminals;
  result._terminals.insert(result._terminals.end(), otherCopy._terminals.begin(), otherCopy._terminals.end());

  for (auto &rule : thisCopy._rules) {
    result.addRule(rule.getLeftValue(), rule.getRightValue()); /* TODO add method with split rule */
  }
  for (auto &rule : otherCopy._rules) {
    result.addRule(rule.getLeftValue(), rule.getRightValue()); /* TODO add method with split rule */
  }

  sort( result._terminals.begin(), result._terminals.end() );
  result._terminals.erase( unique( result._terminals.begin(), result._terminals.end() ), result._terminals.end() );

  result.addRule("S>", thisCopy._start.getValue());
  result.addRule("S>", otherCopy._start.getValue());
//  result._rules.push_back(Rule(++result._nextRuleId, "S", result._start.getValue()));
//  result._rules.push_back(Rule(++result._nextRuleId, "S", otherCopy._start.getValue()));
  result._start = NonTerminal("S");
  result._nonTerminals.push_back(NonTerminal("S"));

  return result;
}

/* Concat */
Grammar Grammar::operator*(const Grammar &other) {
  Grammar thisCopy(*this);
  Grammar otherCopy(other);
  Grammar result;

  thisCopy.modify(thisCopy._id);
  otherCopy.modify(otherCopy._id);

  result._nonTerminals = thisCopy._nonTerminals;
  result._nonTerminals.insert(result._nonTerminals.end(), otherCopy._nonTerminals.begin(), otherCopy._nonTerminals.end());

  result._terminals = thisCopy._terminals;
  result._terminals.insert(result._terminals.end(), otherCopy._terminals.begin(), otherCopy._terminals.end());

  for (auto &rule : thisCopy._rules) {
    result.addRule(rule.getLeftValue(), rule.getRightValue()); /* TODO add method with split rule */
  }
  for (auto &rule : otherCopy._rules) {
    result.addRule(rule.getLeftValue(), rule.getRightValue()); /* TODO add method with split rule */
  }

  sort( result._terminals.begin(), result._terminals.end() );
  result._terminals.erase( unique( result._terminals.begin(), result._terminals.end() ), result._terminals.end() );

  result.addRule("S>", thisCopy._start.getValue() + otherCopy._start.getValue());
//  result._rules.push_back(Rule(++result._nextRuleId, "S", result._start.getValue()));
//  result._rules.push_back(Rule(++result._nextRuleId, "S", otherCopy._start.getValue()));
  result._start = NonTerminal("S");
  result._nonTerminals.push_back(NonTerminal("S"));

  return result;
}


void Grammar::modify(long id) {
  _start.addIndex(id);
  for (auto &nonTerminal : _nonTerminals) {
    nonTerminal.addIndex(id);
  }
  for (auto &rule : _rules) {
    rule.modify(id);
  }
}

long Grammar::get_id() const {
  return _id;
}

void Grammar::set_id(long _id) {
  Grammar::_id = _id;
}

const std::vector<Terminal> &Grammar::get_terminals() const {
  return _terminals;
}

void Grammar::set_terminals(const std::vector<Terminal> &_terminals) {
  Grammar::_terminals = _terminals;
}

const std::vector<NonTerminal> &Grammar::get_nonTerminals() const {
  return _nonTerminals;
}

void Grammar::set_nonTerminals(const std::vector<NonTerminal> &_nonTerminals) {
  Grammar::_nonTerminals = _nonTerminals;
}

const NonTerminal &Grammar::get_start() const {
  return _start;
}

void Grammar::set_start(const NonTerminal &_start) {
  Grammar::_start = _start;
}

const std::vector<Rule> &Grammar::get_rules() const {
  return _rules;
}

void Grammar::set_rules(const std::vector<Rule> &_rules) {
  Grammar::_rules = _rules;
}

long Grammar::get_nextRuleId() {
  return _nextRuleId;
}

void Grammar::set_nextRuleId(long _nextRuleId) {
  Grammar::_nextRuleId = _nextRuleId;
}

void Grammar::addRule(std::string rule) {
  std::vector<std::string> sets = StringManager(rule).splitBy('>');
  if (sets.size() < 2) {
    std::cerr << "Invalid rule" << std::endl;
    exit(1);
  }
  _rules.push_back(Rule(++_nextRuleId, sets.at(0), sets.at(1)));
}

void Grammar::removeRule(long id) {
  for (auto it = _rules.begin();  it != _rules.end() ; it++) {
    if (it->get_id() == id) {
      _rules.erase(it);
    }
  }
}

void Grammar::addRule(std::string left, std::string right) {
  _rules.push_back(Rule(++_nextRuleId, left, right));
}

void Grammar::addRule(const Rule &rule) {
  _rules.push_back(Rule(rule));
}

bool Grammar::chomsky() {
  for (auto &rule : _rules) {
    /* Check for non chomsky rules */
    if (!rule.isChomsky()) return false;
  }

  return true;
}

Grammar Grammar::iterate() {
  Grammar thisCopy(*this);
//  thisCopy.
  return Grammar();
}


