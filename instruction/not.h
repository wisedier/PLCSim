#ifndef PLC_EMULATOR_INSTRUCTION_NOT_H_
#define PLC_EMULATOR_INSTRUCTION_NOT_H_

#include "instruction.h"

namespace plc_emulator {
class NOT : public Instruction {
 public:
  NOT(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetNegation(is_negated);
    SetName("NOT");
  };
  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
