//
// Created by genchev99 on 26.05.19.
//

#include "StringManager.h"
#include <set>
#include <sstream>
#include <algorithm>

StringManager::StringManager() {
  _string = "error";
}

StringManager::StringManager(std::string string) {
  _string = string;
}

std::vector<std::string> StringManager::splitBy(char delimiter) {
  std::vector<std::string> internal;
  std::stringstream ss(_string); // Turn the string into a stream.
  std::string tok;

  while (getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }

  return internal;
}

std::string StringManager::eraseFromString(std::string delimiters) {
  for (char delimiter : delimiters) {
    _string.erase(std::remove (_string.begin(), _string.end(), delimiter), _string.end()); /* Clearing whitespaces */
  }

  return _string;
}
