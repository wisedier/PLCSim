#ifndef PLC_EMULATOR_INSTRUCTION_LE_H_
#define PLC_EMULATOR_INSTRUCTION_LE_H_

#include "instruction.h"

namespace plc_emulator {
class LE : public Instruction {
 public:
  LE(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetNegation(is_negated);
    SetName("LE");
  };

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
