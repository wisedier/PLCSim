#ifndef __PC_EMULATOR_INCLUDE_SFC_MUX_H
#define __PC_EMULATOR_INCLUDE_SFC_MUX_H

#include "sfc.h"

namespace plc_emulator {
class MUX : public SFC {
 public:
  MUX(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("MUX");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
