#ifndef PLC_EMULATOR_INSTRUCTION_DIV_H_
#define PLC_EMULATOR_INSTRUCTION_DIV_H_

#include "instruction.h"

namespace plc_emulator {
class DIV : public Instruction {
 public:
  DIV(ResourceImpl *associated_resource, bool is_negated) {
    SetResource(associated_resource);
    SetNegation(is_negated);
    SetName("DIV");
  };
  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};
}

#endif
