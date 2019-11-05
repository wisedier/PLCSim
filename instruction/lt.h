#ifndef PLC_EMULATOR_INSTRUCTION_LT_H_
#define PLC_EMULATOR_INSTRUCTION_LT_H_

#include "instruction.h"

namespace plc_emulator {
class LT : public Instruction {
 public:
  LT(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetNegation(is_negated);
    SetName("LT");
  };

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
