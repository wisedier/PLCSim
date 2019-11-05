#ifndef __PC_EMULATOR_INCLUDE_SFC_MIN_H
#define __PC_EMULATOR_INCLUDE_SFC_MIN_H

#include "sfc.h"

namespace plc_emulator {
class Min : public SFC {
 public:
  Min(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("MIN");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
