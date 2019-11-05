#ifndef __PC_EMULATOR_INCLUDE_SFC_GTOD_H
#define __PC_EMULATOR_INCLUDE_SFC_GTOD_H

#include "sfc.h"

namespace plc_emulator {
class GTOD : public SFC {
 public:
  GTOD(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("GTOD");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
