//
// Created by genchev99 on 26.05.19.
//

#ifndef GRAMMARS_STRINGMANAGER_H
#define GRAMMARS_STRINGMANAGER_H


#include <string>
#include <vector>

class StringManager {
  std::string _string;
public:
  StringManager();
  StringManager(std::string string);
  std::vector<std::string> splitBy(char delimiters);
  std::string eraseFromString(std::string delimiters);
};


#endif //GRAMMARS_STRINGMANAGER_H
