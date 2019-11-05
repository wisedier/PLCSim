#ifndef PLC_EMULATOR_INSTRUCTION_MUL_H_
#define PLC_EMULATOR_INSTRUCTION_MUL_H_

#include "instruction.h"

namespace plc_emulator {
class MUL : public Instruction {
 public:
  MUL(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetNegation(is_negated);
    SetName("MUL");
  };

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
