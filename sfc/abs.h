#ifndef __PC_EMULATOR_INCLUDE_SFC_ABS_H
#define __PC_EMULATOR_INCLUDE_SFC_ABS_H

#include "sfc.h"

namespace plc_emulator {
class ABS : public SFC {
 public:
  ABS(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("ABS");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
