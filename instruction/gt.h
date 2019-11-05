#ifndef PLC_EMULATOR_INSTRUCTION_GT_H_
#define PLC_EMULATOR_INSTRUCTION_GT_H_

#include "instruction.h"

namespace plc_emulator {
class GT : public Instruction {
 public:
  GT(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetNegation(is_negated);
    SetName("GT");
  };

  void Execute(Variable *curr_result,
               std::vector<Variable *> &ops);
};
}

#endif
