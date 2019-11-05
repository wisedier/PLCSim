#ifndef __PC_EMULATOR_INSTRUCTION_SHL_H_
#define __PC_EMULATOR_INSTRUCTION_SHL_H_

#include "instruction.h"

namespace plc_emulator {
class SHL : public Instruction {
 public:
  SHL(ResourceImpl *associated_resource, bool is_negated) {
    SetName("SHL");
    SetResource(associated_resource);
    SetNegation(is_negated);
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
