#include <iostream>
#include <vector>
#include "Variable.h"
#include "Terminal.h"
#include "Rule.h"
#include "Grammar.h"
#include "GrammarManager.h"
#include "StringManager.h"

bool validate(std::vector<std::string> command) {
  if (command.empty()) return false; /* Empty check */

  if (command.at(0) != "exit"
    && command.at(0) != "saveas"
    && command.at(0) != "close"
    && command.at(0) != "close"
    && command.at(0) != "save"
    && command.at(0) != "help"
    && command.at(0) != "print"
    && command.at(0) != "list"
    && command.at(0) != "union"
    && command.at(0) != "addRule"
    && command.at(0) != "removeRule"
    && command.at(0) != "concat"
    && command.at(0) != "chomsky"
    && command.at(0) != "chomskify"
    && command.at(0) != "iter"
    && command.at(0) != "cyk"
    && command.at(0) != "open") {
    return false;
  }
  if (command.size() < 2) {
    if (command.at(0) == "open"
      || command.at(0) == "saveas"
      || command.at(0) == "print"
      || command.at(0) == "chomskify"
      || command.at(0) == "chomsky"
      || command.at(0) == "iter"
      || command.at(0) == "cyk") {
      return false;
    }
  }
  if (command.size() < 3) {
    if (command.at(0) == "concat"
      || command.at(0) == "removeRule"
      || command.at(0) == "addRule"
      || command.at(0) == "union") {
      return false;
    }
  }

  return true;
}

int main() {
  bool exit = false;
  std::string command;

  GrammarManager  *grammarManager = new GrammarManager();
//  grammarManager->open("/home/genchev99/CPP_Projects/Grammars/grams.txt");
  while (!exit) {
    std::getline(std::cin, command);
    std::vector<std::string> splitCommand = StringManager(command).splitBy(' ');
    bool locked = grammarManager->isLocked();
    if (!validate(splitCommand)) {
      std::cout << "[ Err ] Unsupported command - type \"help\" to check all commands!" << std::endl;
    } else if (splitCommand.at(0) == "exit") {
      exit = true;
    } else if (splitCommand.at(0) == "open") {
      grammarManager->open(splitCommand.at(1));
    } else if (splitCommand.at(0) == "print" && locked) {
      grammarManager->print(std::stoi(splitCommand.at(1)));
    } else if (splitCommand.at(0) == "list" && locked) {
      grammarManager->list();
    } else if (splitCommand.at(0) == "union" && locked) {
      grammarManager->unionGrammars(std::stoi(splitCommand.at(1)), std::stoi(splitCommand.at(2)));
    } else if (splitCommand.at(0) == "concat" && locked) {
      grammarManager->concatGrammars(std::stoi(splitCommand.at(1)), std::stoi(splitCommand.at(2)));
    } else if (splitCommand.at(0) == "addRule" && locked) {
      grammarManager->addRule(std::stoi(splitCommand.at(1)), splitCommand.at(2));
    } else if (splitCommand.at(0) == "removeRule" && locked) {
      grammarManager->removeRule(std::stoi(splitCommand.at(1)), std::stoi(splitCommand.at(2)));
    } else if (splitCommand.at(0) == "cyk" && locked) {
      grammarManager->cyk(std::stoi(splitCommand.at(1)), splitCommand.at(2));
    } else if (splitCommand.at(0) == "chomsky" && locked) {
      grammarManager->chomsky(std::stoi(splitCommand.at(1)));
    } else if (splitCommand.at(0) == "chomskify" && locked) {
      grammarManager->chomskify(std::stoi(splitCommand.at(1)));
    } else if (splitCommand.at(0) == "iter" && locked) {
      grammarManager->iteration(std::stoi(splitCommand.at(1)));
    } else if (splitCommand.at(0) == "help") {
      grammarManager->help();
    } else if (splitCommand.at(0) == "close" && locked) {
      grammarManager->close();
    } else if (splitCommand.at(0) == "saveas" && locked) {
      grammarManager->saveas(splitCommand.at(1));
    } else if (splitCommand.at(0) == "save" && locked) {
      if (splitCommand.size() <= 2) {
        grammarManager->save();
      } else {
        grammarManager->save(std::stoi(splitCommand.at(1)), splitCommand.at(2));
      }
    }
  }

  grammarManager->Destroy();

  return 0;
}