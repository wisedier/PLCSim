#ifndef __PC_EMULATOR_INCLUDE_SFC_LN_H
#define __PC_EMULATOR_INCLUDE_SFC_LN_H

#include "sfc.h"

namespace plc_emulator {
class LN : public SFC {
 public:
  LN(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("LN");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
