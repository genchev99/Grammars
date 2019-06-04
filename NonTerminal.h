//
// Created by genchev99 on 26.05.19.
//

#ifndef GRAMMARS_NONTERMINAL_H
#define GRAMMARS_NONTERMINAL_H


#include <vector>
#include "Variable.h"

class NonTerminal: public Variable {
  std::vector<long> _indexes;
public:
    NonTerminal();
    NonTerminal(std::string nonTerminal);
    NonTerminal(const NonTerminal &other);

    std::string getValue() override;
    std::string getIndexAsString();

    void addIndex(long id) override;

    ~NonTerminal();
};


#endif //GRAMMARS_NONTERMINAL_H
