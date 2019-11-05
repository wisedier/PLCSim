#ifndef PLC_EMULATOR_INSTRUCTION_XOR_H_
#define PLC_EMULATOR_INSTRUCTION_XOR_H_

#include "instruction.h"

namespace plc_emulator {
class XOR : public Instruction {
 public:
  XOR(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetName("XOR");
    SetNegation(is_negated);
  };

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
