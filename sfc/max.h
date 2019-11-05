#ifndef __PC_EMULATOR_INCLUDE_SFC_MAX_H
#define __PC_EMULATOR_INCLUDE_SFC_MAX_H

#include "sfc.h"

namespace plc_emulator {
class Max : public SFC {
 public:
  Max(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("MAX");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
