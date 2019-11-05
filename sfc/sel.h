#ifndef __PC_EMULATOR_INCLUDE_SFC_SEL_H
#define __PC_EMULATOR_INCLUDE_SFC_SEL_H

#include "sfc.h"

namespace plc_emulator {
class SEL : public SFC {
 public:
  SEL(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("SEL");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
