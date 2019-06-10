//
// Created by genchev99 on 26.05.19.
//

#ifndef GRAMMARS_GRAMMARMANAGER_H
#define GRAMMARS_GRAMMARMANAGER_H


#include "Grammar.h"

class GrammarManager {
  std::string _source;
  bool _lock;
  std::vector<Grammar *> _grammars;
  /* Utils */
  long _nextGrammarId;
public:
    GrammarManager();
    Grammar *getGrammar(long id);
    void open(std::string path);
    void save();
    void save(long id, std::string path);
    void saveas(std::string path);
    void list();
    void print(long id);
    void addRule(long id, std::string rule);
    void removeRule(long grammar, long rule);
    void unionGrammars(long left, long right);
    void concatGrammars(long left, long right);
    void iteration(long id);
    void chomsky(long id);
    void chomskify(long id);
    void cyk(long id, std::string word);
    void help();
    void close();

    bool isLocked();
    void Destroy();
};


#endif //GRAMMARS_GRAMMARMANAGER_H
