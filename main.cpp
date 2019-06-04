#include <iostream>
#include <vector>
#include "Variable.h"
#include "Terminal.h"
#include "Rule.h"
#include "Grammar.h"
#include "GrammarManager.h"

int main() {
  /*std::vector<Variable *> variables;
  variables.push_back(new Terminal("a"));
  variables.push_back(new Terminal("as"));
  variables.push_back(new Terminal("asd"));

  for (const auto &variable : variables) {
    std::cout << variable->getValue() << std::endl;
  }*/
  /*Rule rule(1, "S", "aSa");
  Rule rule2(rule);
  rule.modify(2);*/

  /*Grammar grammar1(1, "({S, B, B1}; {a, b}; S; {S>b|aBB|B|BB1|BBB, B>baba, B1>a})");
  Grammar grammar2(2, "({S, A}; {a, b}; S; {S>a|b|AA, A>b})");
  Grammar grammar3 = grammar1+grammar2;
  std::vector<Grammar> grammars;
  grammars.push_back(grammar1);
  grammars.push_back(grammar2);
  grammars.push_back(grammar3);

  (grammars.end() -1)->set_id(3);

  for (auto &grammar : grammars) {
    grammar.print();
  }*/
  GrammarManager  grammarManager;
  grammarManager.open("/home/genchev99/CPP_Projects/Grammars/grams.txt");
  grammarManager.list();
  grammarManager.print(1);
  grammarManager.print(2);
  grammarManager.addRule(2, "S>aaaa");
  grammarManager.print(2);
  grammarManager.removeRule(2, 3);
  grammarManager.print(2);

  grammarManager.unionGrammars(1, 2);
  grammarManager.print(3);

  grammarManager.concatGrammars(1, 2);
  grammarManager.print(4);

  grammarManager.iteration(1);
  grammarManager.print(5);

  grammarManager.chomskify(2);
  grammarManager.print(6);

  return 0;
}