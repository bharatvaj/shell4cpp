#ifndef _SHELL_H
#define _SHELL_H

#include <iostream>
#include <string>
#include <cstdarg>
#include <functional>
#include <map>
#include <vector>

#include <shell4cpp/Operation.hpp>
#define _SHELL_PORT 50000

namespace shell4cpp {
class Shell {
private:
  std::map<std::string, Operation *> operations;
  std::function<void(int)> exitHandler = [](int) {};
  std::string shellIcon;

  bool endsWith(const std::string &s, const std::string &suffix) {
    return s.size() >= suffix.size() &&
           s.substr(s.size() - suffix.size()) == suffix;
  }

  std::vector<std::string> split(const std::string &s,
                                 const std::string &delimiter,
                                 const bool &removeEmptyEntries = false) {
    std::vector<std::string> tokens;

    for (size_t start = 0, end; start < s.length();
         start = end + delimiter.length()) {
      size_t position = s.find(delimiter, start);
      end = position != std::string::npos ? position : s.length();

      std::string token = s.substr(start, end - start);
      if (!removeEmptyEntries || !token.empty()) {
        tokens.push_back(token);
      }
    }

    if (!removeEmptyEntries && (s.empty() || endsWith(s, delimiter))) {
      tokens.push_back("");
    }

    return tokens;
  }

public:
  Shell(std::string shellIcon) : shellIcon(shellIcon) {}
  void addOperation(std::string op,
                    std::function<void(std::vector<std::string>)> opFunc) {
    // operations[op] = opFunc;
  }
  void addOperation(Operation *op) { operations[op->name] = op; }

  std::map<std::string, Operation *> getOperations() { return operations; }
  // TODO
  // void addOperation(Operation op){
  //   operations[op.name] = op;
  // }
  void execute(std::vector<std::string> ins) {
    if (ins.size() == 0) {
      return;
    }
    Operation *op = operations[ins[0]];
    if (op == nullptr) {
      println(std::string(ins[0]) + ": operation not found");
      return;
    }
    std::function<void(Operation, std::vector<std::string>)> func = op->fp;
    ins.erase(ins.begin(), ins.begin() + 1);
    try {
      func(*op, ins);
    } catch (std::bad_function_call bfc) {
      println(std::string(ins[0]) + ": operation not found");
    }
  }

  void print(std::string message) { std::cout << message; }

  void println(std::string message) { std::cout << message << std::endl; }

  void start() {
    std::string in;
    print(shellIcon);
    while (std::getline(std::cin, in)) {
      std::vector<std::string> ins = split(in, " ", true);
      execute(ins);
      print(shellIcon);
    }
  }

  void setOnShellExit(std::function<void(int)> func) { exitHandler = func; }
};
} // namespace shell4cpp
#endif
