#ifndef PLC_EMULATOR_INSTRUCTION_OR_H_
#define PLC_EMULATOR_INSTRUCTION_OR_H_

#include "instruction.h"

namespace plc_emulator {
class OR : public Instruction {
 public:
  OR(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetNegation(is_negated);
    SetName("OR");
  };

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
