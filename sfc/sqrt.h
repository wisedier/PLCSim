#ifndef __PC_EMULATOR_INCLUDE_SFC_SQRT_H
#define __PC_EMULATOR_INCLUDE_SFC_SQRT_H

#include "sfc.h"

namespace plc_emulator {
class SQRT : public SFC {
 public:
  SQRT(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("SQRT");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
