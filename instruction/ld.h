#ifndef PLC_EMULATOR_INSTRUCTION_LD_H_
#define PLC_EMULATOR_INSTRUCTION_LD_H_

#include "instruction.h"

namespace plc_emulator {
class LD : public Instruction {
 public:
  LD(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetNegation(is_negated);
    SetName("LD");
  };

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
