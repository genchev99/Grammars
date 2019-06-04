//
// Created by genchev99 on 26.05.19.
//

#ifndef GRAMMARS_VARIABLE_H
#define GRAMMARS_VARIABLE_H


#include <string>
#include <vector>

class Variable {
protected:
  std::string _value;
public:
  Variable();
  Variable(std::string variable);
  Variable(const Variable &other);

  bool isTerminal();
  bool isEpsilon();

  void setValue(std::string value);

  virtual std::string getValue() = 0;
  virtual void addIndex(long id) = 0;

  bool operator==(const Variable &rhs) const;
  bool operator!=(const Variable &rhs) const;

  bool operator<(const Variable &rhs) const;
  bool operator>(const Variable &rhs) const;
  bool operator<=(const Variable &rhs) const;
  bool operator>=(const Variable &rhs) const;

  virtual void Destroy() = 0;
//  ~Variable();
};


#endif //GRAMMARS_VARIABLE_H
