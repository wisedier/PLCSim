#ifndef __PC_EMULATOR_INCLUDE_SFC_TAN_H
#define __PC_EMULATOR_INCLUDE_SFC_TAN_H

#include "sfc.h"

namespace plc_emulator {
class TAN : public SFC {
 public:
  TAN(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("TAN");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
