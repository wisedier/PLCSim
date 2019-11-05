#ifndef __PLC_EMULATOR_INSTRUCTION_SHR_H_
#define __PLC_EMULATOR_INSTRUCTION_SHR_H_

#include "instruction.h"

namespace plc_emulator {
class SHR : public Instruction {
 public:
  SHR(ResourceImpl *associated_resource, bool is_negated) {
    SetName("SHR");
    SetResource(associated_resource);
    SetNegation(is_negated);
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
