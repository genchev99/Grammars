//
// Created by genchev99 on 26.05.19.
//

#ifndef GRAMMARS_RULE_H
#define GRAMMARS_RULE_H


#include "NonTerminal.h"

class Rule {
  long _id;
  NonTerminal _left;
  std::vector<Variable *> _right;
public:
  Rule();
  Rule(long id, std::string left, std::string right);
  Rule(const Rule &other);

  std::string getLeftValue();
  std::string getRightValue();

  void print();
  void modify(long id);

  bool isChomsky();

  long get_id();
};




#endif //GRAMMARS_RULE_H
