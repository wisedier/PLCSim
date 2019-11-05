#ifndef PLC_EMULATOR_INSTRUCTION_NE_H_
#define PLC_EMULATOR_INSTRUCTION_NE_H_

#include "instruction.h"

namespace plc_emulator {
class NE : public Instruction {
 public:
  NE(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetNegation(is_negated);
    SetName("NE");
  };

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
