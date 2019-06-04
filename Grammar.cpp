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
      _rules.push_back(new Rule(++_nextRuleId, splitRule.at(0), item));
    }
  }
}

Grammar::Grammar(const Grammar &other) {
//  std::cout << "Grammar copy constructor" << std::endl;
  _id = other._id;
  _nextRuleId =  0;
  _nonTerminals = other._nonTerminals;
  _terminals = other._terminals;
  _start = other._start;
  for (auto rule : other._rules) {
    this->addRule(rule->getLeftValue(), rule->getRightValue());
  }
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
    rule->print();
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
    result.addRule(rule->getLeftValue(), rule->getRightValue()); /* TODO add method with split rule */
  }
  for (auto &rule : otherCopy._rules) {
    result.addRule(rule->getLeftValue(), rule->getRightValue()); /* TODO add method with split rule */
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
    result.addRule(rule->getLeftValue(), rule->getRightValue()); /* TODO add method with split rule */
  }
  for (auto &rule : otherCopy._rules) {
    result.addRule(rule->getLeftValue(), rule->getRightValue()); /* TODO add method with split rule */
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
    rule->modify(id);
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

const std::vector<Rule *> &Grammar::get_rules() const {
  return _rules;
}

void Grammar::set_rules(const std::vector<Rule> &rules) {
  for (auto &rule : rules) {
    _rules.push_back(new Rule(rule));
  }
//  Grammar::_rules = _rules;
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
  _rules.push_back(new Rule(++_nextRuleId, sets.at(0), sets.at(1)));
}

void Grammar::removeRule(long id) {
  for (auto it = _rules.begin();  it != _rules.end() ; it++) {
    if ((*it)->get_id() == id) {
//      delete (*it);
      (*it)->Destroy();
      _rules.erase(it);
    }
  }
}

void Grammar::addRule(std::string left, std::string right) {
  Rule *rule = new Rule(++_nextRuleId, std::move(left), std::move(right));
  _rules.push_back(rule);
//  rule->Destroy();
}

void Grammar::addRule(const Rule &rule) {
  _rules.emplace_back(new Rule(rule));
}

bool Grammar::chomsky() {
  for (auto &rule : _rules) {
    /* Check for non chomsky rules */
    if (!rule->isChomsky()) return false;
  }

  return true;
}

Grammar Grammar::iterate() {
  Grammar result(*this);
  result.modify(result.get_id());

  result.addRule("S", result._start.getValue() + "S");
  result._start = NonTerminal("S");
  result._nonTerminals.push_back(result._start);

  return result;
}

std::vector<std::pair<NonTerminal, NonTerminal>> getCombinations(const std::string &left, const std::string &right, std::vector<std::pair<std::string, std::vector<NonTerminal>>> pairs) {
  std::vector<std::pair<NonTerminal, NonTerminal>> result;
  std::vector<NonTerminal> leftNonTerminals;
  std::vector<NonTerminal> rightNonTerminals;
  for (auto &pair : pairs) {
    if (left == pair.first) { leftNonTerminals = pair.second; }
    if (right == pair.first) { rightNonTerminals = pair.second; }
  }

  for (auto &leftNonTerminal : leftNonTerminals) {
    for (auto &rightNonTerminal : rightNonTerminals) {
      result.push_back(std::make_pair(leftNonTerminal, rightNonTerminal));
    }
  }

  return result;
}

bool isPair(std::vector<std::pair<std::string, std::vector<NonTerminal>>> pairs, std::string word) {
  for (auto &item : pairs) {
    if (item.first == word) {
      return true;
    }
  }

  return false;
}

std::string joinNonTerminals(std::pair<NonTerminal, NonTerminal> combination) {
  return combination.first.getValue() + combination.second.getValue();
}

bool Grammar::cyk(std::string word) {
  if (!chomsky() || word.empty()) {
    std::cerr << "Grammar error" << std::endl;
    return false;
  }

  std::vector<std::pair<std::string, std::vector<NonTerminal>>> pairs; /* Where is the hashset ;( */
  for (unsigned long i = 1; i <= word.size(); ++i) { /* Word length */
    for (unsigned long k = 0; k < word.size() - i + 1; ++k) { /* Starting position */
      std::string currentSubString = word.substr(k, i); /* Substring from starting position k and length i */
      if (currentSubString.size() == 1) {
        std::vector<NonTerminal> leftNonTerminals = getNonTerminalsFromImplication(currentSubString);
        if (!isPair(pairs, currentSubString)) pairs.push_back(std::make_pair(currentSubString, leftNonTerminals));
      } else {
        for (unsigned long j = 1; j < currentSubString.size(); ++j) { /* Sub parts split */
          std::string left = currentSubString.substr(0, j);
          std::string right = currentSubString.substr(j, currentSubString.size() - j);
          std::vector<std::pair<NonTerminal, NonTerminal>> combinations = getCombinations(left, right, pairs);
          std::vector<NonTerminal> matches;
          for (auto &combination : combinations) {
            std::vector<NonTerminal> currentMatches = getNonTerminalsFromImplication(joinNonTerminals(combination));
            matches.insert(matches.end(), currentMatches.begin(), currentMatches.end());
          }

          if (!isPair(pairs, currentSubString)) pairs.push_back(std::make_pair(currentSubString, matches));
        }
      }
      /*for (auto &pair : pairs) {
        std::cout << pair.first;
        if (pair.first == word) {
          for (auto &term : pair.second) {
            std::cout << term.getValue();
            if (term.getValue() == _start.getValue()) return true;
          }
        }
      }*/


    }
  }

  for (auto &pair : pairs) {
    std::cout << "word: " << pair.first;
    std::cout << word << std::endl;
    if (pair.first == word) {
      for (auto &term : pair.second) {
        std::cout << " value: " << term.getValue();
        if (term.getValue() == _start.getValue()) return true;
      }
    }
    std::cout << std::endl;
  }


  return false;
}

std::vector<NonTerminal> Grammar::getNonTerminalsFromImplication(std::string word) {
  std::vector<NonTerminal> nonTerminals;

  for (auto &rule : _rules) {
    if (rule->getRightValue() == word) {
      nonTerminals.push_back(rule->getRightValue());
    }
  }

  return nonTerminals;
}

char Grammar::ensureNonTerminalSymbol() {
  for (char i = 'A'; i <= 'Z'; ++i) {
    bool found = false;
    for (auto &nonTerminal : _nonTerminals) {
      if (nonTerminal.getValue().at(0) == i) found = true;
    }

    if (!found) {
      return i;
    }
  }

  return '@';
}

bool Grammar::hasOneRule(NonTerminal nonTerminal) {
  int occurrences = 0;
  for (auto &rule : _rules) {
    if (rule->getLeftValue() == nonTerminal.getValue()) {
      occurrences++;
    }
  }

  return occurrences == 1;
}

std::vector<std::pair<Terminal, NonTerminal>> Grammar::getReverseImplication() {
  std::vector<std::pair <Terminal, NonTerminal>> result;
  long long newNonTerminalsCounter = 0;
  for (auto &terminal : _terminals) {
    bool found = false;
    for (auto &rule : _rules) {
      auto ruleParts = rule->getRight();
      if (ruleParts.size() == 1 && ruleParts.at(0)->getValue() == terminal.getValue() && hasOneRule(rule->getLeft())) {
        result.push_back(std::make_pair(terminal, rule->getLeft()));
        found = true;
      }
    }
    if (!found) {
      result.push_back(std::make_pair(terminal, NonTerminal(std::string(1, ensureNonTerminalSymbol()) + std::to_string(++newNonTerminalsCounter))));
    }
  }

  return result;
}

NonTerminal getNonTerminalFromReverse(std::vector<std::pair<Terminal, NonTerminal>> pairs, Terminal terminal) {
  for (auto &pair : pairs) {
    if (pair.first.getValue() == terminal.getValue()) return pair.second.getValue();
  }

  return NonTerminal("@");
}

std::string getPackedNonTerminals(std::vector<Variable *> variables) {
  std::string result;
  for (unsigned long i = 1; i < variables.size(); ++i) {
    result += variables.at(i)->getValue();
  }

  return result;
}

std::vector<Rule *> Grammar::getRulesFrom(NonTerminal nonTerminal) {
  std::vector<Rule *> result;
  for (auto &rule : _rules) {
    if (rule->getLeftValue() == nonTerminal.getValue()) {
      result.push_back(rule);
    }
  }

  return result;
}

Grammar Grammar::chomskify() {
//  Grammar result(*this);
  std::vector<std::pair <Terminal, NonTerminal>> linkedNonTerminals = getReverseImplication();

  /* First step */
  for (auto &rule : _rules) {
    auto variables = rule->getRight();
    for (auto &variable : variables) {
      if (variable->isTerminal() && variables.size() != 1) {
        NonTerminal nonTerminal = getNonTerminalFromReverse(linkedNonTerminals, variable->getValue());
        if (!ruleExists(nonTerminal, *variable)) this->addRule(nonTerminal.getValue(), variable->getValue());
        variable->setValue(nonTerminal.getValue());
      }
    }
  }

  /* Sec step */
  int counter = 0;
  std::vector<long long> rulesToRemove;
  unsigned long size = _rules.size();
  char unusedChar = ensureNonTerminalSymbol();
  for (unsigned int i = 0; i < size; ++i) {
    auto variables = _rules.at(i)->getRight();
    if (variables.size() > 2) {
      std::string nonTerminalString = std::string(1, unusedChar) + std::to_string(++counter);
      this->addRule(_rules.at(i)->getLeftValue(), variables.at(0)->getValue() + nonTerminalString);
      this->addRule(nonTerminalString, getPackedNonTerminals(variables));
      rulesToRemove.push_back(_rules.at(i)->get_id());
      size = _rules.size();
    }
  }
  for (auto &toRemove : rulesToRemove) { this->removeRule(toRemove); } /* Removing the wrapped rules */
  /* Step 3 remove epsilon rules */

  /* Step 4 remove single non Terminals */
  rulesToRemove.clear();
  for (auto &rule : _rules) {
    auto variables = rule->getRight();
    if (variables.size() == 1 && !variables.at(0)->isTerminal()) {
      std::vector<Rule *> nestedRules = getRulesFrom(variables.at(0)->getValue());
      for (auto &nestedRule : nestedRules) {
        this->addRule(rule->getLeftValue(), nestedRule->getRightValue());
        rulesToRemove.push_back(rule->get_id());
      }
    }
  }
  for (auto &toRemove : rulesToRemove) { this->removeRule(toRemove); } /* Removing the nested rules */


  return *this;
}

bool Grammar::ruleExists(NonTerminal left, Terminal right) {
  for (auto &rule : _rules) {
    if (rule->getLeftValue() == left.getValue() && rule->getRightValue() == right.getValue()) {
      return true;
    }
  }
  return false;
}

/*Grammar::~Grammar() {
  for (auto itr : _rules) {
    std::cout << itr << std::endl;
    itr->Destroy();
  }
}*/

void Grammar::Destroy() {
  for (auto itr : _rules) {
//    std::cout << itr << std::endl;
    itr->Destroy();
  }
  delete(this);
}



