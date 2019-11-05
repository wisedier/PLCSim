#ifndef PLC_EMULATOR_INSTRUCTION_ADD_H_
#define PLC_EMULATOR_INSTRUCTION_ADD_H_

#include "instruction.h"

namespace plc_emulator {
class ADD : public Instruction {
 public:
  ADD(ResourceImpl *associated_resource, bool is_negated) {
    SetName("ADD");
    SetNegation(is_negated);
    SetResource(associated_resource);
  };

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
