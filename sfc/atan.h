#ifndef __PC_EMULATOR_INCLUDE_SFC_ATAN_H
#define __PC_EMULATOR_INCLUDE_SFC_ATAN_H

#include "sfc.h"

namespace plc_emulator {
class ATAN : public SFC {
 public:
  ATAN(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("ATAN");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
