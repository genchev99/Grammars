//
// Created by genchev99 on 26.05.19.
//

#ifndef GRAMMARS_GRAMMARMANAGER_H
#define GRAMMARS_GRAMMARMANAGER_H


#include "Grammar.h"

class GrammarManager {
  std::vector<Grammar> _grammars;
  /* Utils */
  long _nextGrammarId;
public:
    GrammarManager();
    Grammar *getGrammar(long id);
    void open(std::string path);
    void list();
    void print(long id);
    void addRule(long id, std::string rule);
    void removeRule(long grammar, long rule);
    void unionGrammars(long left, long right);
    void concatGrammars(long left, long right);
    void iteration(long id);
    void chomsky(long id);
};


#endif //GRAMMARS_GRAMMARMANAGER_H
