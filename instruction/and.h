#ifndef PLC_EMULATOR_INSTRUCTION_AND_H_
#define PLC_EMULATOR_INSTRUCTION_AND_H_

#include "instruction.h"

namespace plc_emulator {
class AND : public Instruction {
 public:
  AND(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetNegation(is_negated);
    SetName("AND");
  };

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
