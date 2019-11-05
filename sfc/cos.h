#ifndef __PC_EMULATOR_INCLUDE_SFC_COS_H
#define __PC_EMULATOR_INCLUDE_SFC_COS_H

#include "sfc.h"

namespace plc_emulator {
class COS : public SFC {
 public:
  COS(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("COS");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
