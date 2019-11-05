#ifndef PLC_EMULATOR_INSTRUCTION_INSTRUCTION_H_
#define PLC_EMULATOR_INSTRUCTION_INSTRUCTION_H_

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "config.pb.h"
#include "config.h"
#include "resource.h"
#include "logger.h"

namespace plc_emulator {
class Instruction {
 private:
  std::string name_;
  bool is_negated_;
  ResourceImpl *associated_resource_;
 public:
  virtual void Execute(Variable *curr_result,
                       std::vector<Variable *> &ops) = 0;

  void SetName(const std::string &name) {
    name_ = name;
  }

  void SetNegation(bool negation) {
    is_negated_ = negation;
  }

  void SetResource(ResourceImpl *resource) {
    associated_resource_ = resource;
  }
};
}

#endif
