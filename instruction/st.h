#ifndef PLC_EMULATOR_INSTRUCTION_ST_H_
#define PLC_EMULATOR_INSTRUCTION_ST_H_

#include "instruction.h"

namespace plc_emulator {
class ST : public Instruction {
 public:
  ST(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetName("ST");
    SetNegation(is_negated);
  };
  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
