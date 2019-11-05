#ifndef __PC_EMULATOR_INCLUDE_SFC_LIMIT_H
#define __PC_EMULATOR_INCLUDE_SFC_LIMIT_H

#include "sfc.h"

namespace plc_emulator {
class LIMIT : public SFC {
 public:
  LIMIT(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("LIMIT");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
