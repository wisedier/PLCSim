#ifndef PLC_EMULATOR_INSTRUCTION_MOD_H_
#define PLC_EMULATOR_INSTRUCTION_MOD_H_

#include "instruction.h"

namespace plc_emulator {
class Mod : public Instruction {
 public:
  Mod(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetNegation(is_negated);
    SetName("MOD");
  };

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
