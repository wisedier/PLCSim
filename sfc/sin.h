#ifndef __PC_EMULATOR_INCLUDE_SFC_SIN_H
#define __PC_EMULATOR_INCLUDE_SFC_SIN_H

#include "sfc.h"

namespace plc_emulator {
class SIN : public SFC {
 public:
  SIN(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("SIN");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
