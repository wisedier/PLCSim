#ifndef PLC_EMULATOR_INSTRUCTION_SUB_H_
#define PLC_EMULATOR_INSTRUCTION_SUB_H_

#include "instruction.h"

namespace plc_emulator {
class SUB : public Instruction {
 public:
  SUB(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetName("SUB");
    SetNegation(is_negated);
  };

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
