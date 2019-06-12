//
// Created by genchev99 on 26.05.19.
//

#include <iostream>
#include <fstream>
#include "GrammarManager.h"

GrammarManager::GrammarManager() {
  _nextGrammarId = 0;
  _lock = false;
}

void GrammarManager::open(std::string path) {
  this->close();
  _grammars.clear(); /* Clearing preload grammars */
  _lock = true;
  _source = path;
  _nextGrammarId = 0;
  std::string line;
  std::ifstream grammarFile (path);
  if (grammarFile.is_open()) {
    while (getline(grammarFile, line)) {
      _grammars.push_back(new Grammar(++_nextGrammarId, line));
    }
    grammarFile.close();
  } else {
    std::cerr << "[ Err ] Unable to open file at: " + path  << std::endl;
    return;
  }

  std::cout << "[ * ] Loaded grammars: " << _grammars.size() << std::endl;
}

void GrammarManager::list() {
  std::cout << "[ * ] Grammars: ";
  const unsigned long grammarsSize = _grammars.size();
  for (unsigned long i = 0; i < grammarsSize; ++i) {
    std::cout << _grammars.at(i)->get_id();
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
    if (grammar->get_id() == id) return grammar;
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
  Grammar *leftGrammar = new Grammar(*getGrammar(left));
  Grammar *rightGrammar = new Grammar(*getGrammar(right));
  Grammar *uni = new Grammar(*leftGrammar + *rightGrammar);
  _grammars.emplace_back(uni);
  (*(_grammars.end() -1))->set_id(++_nextGrammarId); /* Nasty... */

  std::cout << "[ * ] New Grammar: " << (*(_grammars.end() -1))->get_id() << std::endl;
  leftGrammar->Destroy();
  rightGrammar->Destroy();
}

void GrammarManager::concatGrammars(long left, long right) {
  Grammar *leftGrammar = new Grammar(*getGrammar(left));
  Grammar *rightGrammar = new Grammar(*getGrammar(right));

  _grammars.emplace_back(new Grammar(*leftGrammar * *rightGrammar));
  (*(_grammars.end() -1))->set_id(++_nextGrammarId); /* Nasty... */

  std::cout << "[ * ] New Grammar: " << (*(_grammars.end() -1))->get_id() << std::endl;
  leftGrammar->Destroy();
  rightGrammar->Destroy();
}

void GrammarManager::chomsky(long id) {
  bool chomsky = getGrammar(id)->chomsky();
  std::cout << "[ * ] The grammar is " << (chomsky? "": "not") << "in chomsky form!" << std::endl;
}

void GrammarManager::iteration(long id) {
  Grammar *copy = new Grammar(*getGrammar(id));
  copy->iterate();

  _grammars.push_back(copy);
  (*(_grammars.end() -1))->set_id(++_nextGrammarId);
  std::cout << "[ * ] New Grammar: " << (*(_grammars.end() -1))->get_id() << std::endl;
}

void GrammarManager::chomskify(long id) {
  Grammar *grammar = new Grammar(*getGrammar(id));
  grammar->chomskify();

  _grammars.push_back(grammar);
  (*(_grammars.end() -1))->set_id(++_nextGrammarId);
  std::cout << "[ * ] New Grammar: " << (*(_grammars.end() -1))->get_id() << std::endl;
}

void GrammarManager::Destroy() {
  for (auto itr : _grammars) {
//    std::cout << itr << std::endl;
    itr->Destroy();
  }

  delete(this);
}

void GrammarManager::cyk(long id, std::string word) {
  bool contains = getGrammar(id)->cyk(word);

  std::cout << "The word ~ " << word << " ~ is " << (contains? "": "not") << " containing" << std::endl;
}

void GrammarManager::help() {
  std::cout << "[ H ] open <path> - opens grammars's file" << std::endl;
}

void GrammarManager::close() {
  for (auto itr : _grammars) {
    itr->Destroy();
  }

  _grammars.clear();
  _lock = false;
}

bool GrammarManager::isLocked() {
  return _lock;
}

void GrammarManager::saveas(std::string path) {
  std::ofstream newFile(path, std::ios_base::app);
  if(newFile.is_open()) {
    for (auto &grammar : _grammars) {
      newFile << grammar->getString() << "\n";
    }
  } else {
    std::cerr << "[ Err ] Unable to handle the file";
  }

  newFile.close();
}

void GrammarManager::save() {
  std::ofstream newFile(_source);
  if(newFile.is_open()) {
    for (auto &grammar : _grammars) {
      newFile << grammar->getString() << "\n";
    }
  } else {
    std::cerr << "[ Err ] Unable to handle the file";
  }

  newFile.close();
}

void GrammarManager::save(long id, std::string path) {
  std::ofstream newFile(path, std::ios_base::app);
  if(newFile.is_open()) {
    newFile << getGrammar(id)->getString() << "\n";
  } else {
    std::cerr << "[ Err ] Unable to handle the file";
  }

  newFile.close();
}
