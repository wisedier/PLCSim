#ifndef __PC_EMULATOR_INCLUDE_SFC_ACOS_H
#define __PC_EMULATOR_INCLUDE_SFC_ACOS_H

#include "sfc.h"

namespace plc_emulator {
class ACOS : public SFC {
 public:
  ACOS(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("ACOS");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
