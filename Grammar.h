//
// Created by genchev99 on 26.05.19.
//

#ifndef GRAMMARS_GRAMMAR_H
#define GRAMMARS_GRAMMAR_H


#include <vector>
#include "Terminal.h"
#include "NonTerminal.h"
#include "Rule.h"

class Grammar {
  long _id;
  std::vector<Terminal> _terminals;
  std::vector<NonTerminal> _nonTerminals;
  NonTerminal _start;
  std::vector<Rule *> _rules;

  /*  utils */
  long _nextRuleId;
public:
  Grammar();
  Grammar(long id, std::string grammar);
  Grammar(const Grammar &other);
  Grammar operator+(const Grammar &other);
  Grammar operator*(const Grammar &other);

  void print();
  void modify(long id);

  void addRule(const Rule &rule);
  void addRule(std::string rule);
  void addRule(std::string left, std::string right);
  void removeRule(long id);

  char ensureNonTerminalSymbol();
  bool hasOneRule(NonTerminal nonTerminal);
  bool ruleExists(NonTerminal left, Terminal right);
  std::vector<Rule *> getRulesFrom(NonTerminal nonTerminal);
  std::vector<std::pair<Terminal, NonTerminal>> getReverseImplication();


  Grammar iterate();
  Grammar chomskify();
  bool chomsky();
  bool cyk(std::string word);
//  bool cyk2(std::string word);
  std::vector<NonTerminal> getNonTerminalsFromImplication(std::string word);
  /* Getters and setters */
  long get_id() const;
  void set_id(long _id);
  const std::vector<Terminal> &get_terminals() const;
  void set_terminals(const std::vector<Terminal> &_terminals);
  const std::vector<NonTerminal> &get_nonTerminals() const;
  void set_nonTerminals(const std::vector<NonTerminal> &_nonTerminals);
  const NonTerminal &get_start() const;
  void set_start(const NonTerminal &_start);
  const std::vector<Rule *> &get_rules() const;
  void set_rules(const std::vector<Rule> &_rules);
  long get_nextRuleId();
  void set_nextRuleId(long _nextRuleId);

//  ~Grammar();
  void Destroy();
};


#endif //GRAMMARS_GRAMMAR_H
