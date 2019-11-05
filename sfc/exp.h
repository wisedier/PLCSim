#ifndef __PC_EMULATOR_INCLUDE_SFC_EXP_H
#define __PC_EMULATOR_INCLUDE_SFC_EXP_H

#include "sfc.h"

namespace plc_emulator {
class EXP : public SFC {
 public:
  EXP(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("EXP");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
