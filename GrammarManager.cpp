//
// Created by genchev99 on 26.05.19.
//

#include <iostream>
#include <fstream>
#include "GrammarManager.h"

GrammarManager::GrammarManager() {
  _nextGrammarId = 0;
}

void GrammarManager::open(std::string path) {
  _grammars.clear(); /* Clearing preload grammars */
  _nextGrammarId = 0;
  std::string line;
  std::ifstream grammarFile (path);
  if (grammarFile.is_open()) {

    while (getline (grammarFile, line)) {
      _grammars.push_back(Grammar(++_nextGrammarId, line));
    }
    grammarFile.close();
  } else {
    std::cerr << "Unable to open file at: " + path  << std::endl;
    return;
  }

  std::cout << "[ * ] Loaded grammars: " << _grammars.size() << std::endl;
}

void GrammarManager::list() {
  std::cout << "[ * ] Grammars: ";
  const unsigned long grammarsSize = _grammars.size();
  for (unsigned long i = 0; i < grammarsSize; ++i) {
    std::cout << _grammars.at(i).get_id();
    if (i != grammarsSize -1) {
      std::cout << ", ";
    }
  }

  std::cout << std::endl;
}

void GrammarManager::print(long id) {
  getGrammar(id)->print();
}

Grammar * GrammarManager::getGrammar(long id) {
  for (auto &grammar : _grammars) {
    if (grammar.get_id() == id) return &grammar;
  }

  return new Grammar();
}

void GrammarManager::addRule(long id, std::string rule) {
  getGrammar(id)->addRule(rule);
}

void GrammarManager::removeRule(long grammar, long rule) {
  getGrammar(grammar)->removeRule(rule);
}

void GrammarManager::unionGrammars(long left, long right) {
  Grammar leftGrammar = *getGrammar(left);
  Grammar rightGrammar = *getGrammar(right);
//  Grammar unioned = leftGrammar + rightGrammar;
  _grammars.push_back((leftGrammar + rightGrammar));
  (_grammars.end() -1)->set_id(++_nextGrammarId); /* Nasty... */

  std::cout << "[ * ] New Grammar: " << (_grammars.end() -1 )->get_id() << std::endl;
}

void GrammarManager::concatGrammars(long left, long right) {
  Grammar leftGrammar = *getGrammar(left);
  Grammar rightGrammar = *getGrammar(right);
  _grammars.push_back((leftGrammar * rightGrammar));
  (_grammars.end() -1)->set_id(++_nextGrammarId); /* Nasty... */

  std::cout << "[ * ] New Grammar: " << (_grammars.end() -1 )->get_id() << std::endl;
}

void GrammarManager::chomsky(long id) {
  bool chomsky = getGrammar(id)->chomsky();
  std::cout << "[ * ] The grammar is " << (chomsky? "": "not") << "in chomsky form!";
}

void GrammarManager::iteration(long id) {
  Grammar grammar = getGrammar(id)->;
}
