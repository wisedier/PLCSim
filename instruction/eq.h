#ifndef PLC_EMULATOR_INSTRUCTION_EQ_H_
#define PLC_EMULATOR_INSTRUCTION_EQ_H_

#include "instruction.h"

namespace plc_emulator {
class EQ : public Instruction {
 public:
  EQ(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetNegation(is_negated);
    SetName("EQ");
  };

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
