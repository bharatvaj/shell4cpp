#ifndef _OPERATION_H
#define _OPERATION_H
#include <functional>
#include <iostream>
#include <vector>
namespace shell4cpp {
class Operation {
public:
  std::string name;
  std::string description;
  std::function<void(Operation, std::vector<std::string>)> fp;
  std::string usage;
  Operation(std::string name, std::string description,
            std::function<void(Operation, std::vector<std::string>)> fp,
            std::string usage)
      : name(name), description(description), fp(fp),
        usage(usage) {}
};
}
#endif
