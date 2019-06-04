//
// Created by genchev99 on 26.05.19.
//

#ifndef GRAMMARS_TERMINAL_H
#define GRAMMARS_TERMINAL_H


#include "Variable.h"

class Terminal: public Variable {
public:
    Terminal();
    Terminal(std::string terminal);
    Terminal(const Variable &other);
    Terminal(const Terminal &other);

    std::string getValue() override;
    void addIndex(long id) override;

  void Destroy() override;
//    ~Terminal();
};


#endif //GRAMMARS_TERMINAL_H
