#ifndef __PC_EMULATOR_INCLUDE_SFC_LOG_H
#define __PC_EMULATOR_INCLUDE_SFC_LOG_H

#include "sfc.h"

namespace plc_emulator {
class LOG : public SFC {
 public:
  LOG(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("LOG");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
