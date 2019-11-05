#ifndef __PC_EMULATOR_INCLUDE_SFC_ASIN_H
#define __PC_EMULATOR_INCLUDE_SFC_ASIN_H

#include "sfc.h"

namespace plc_emulator {
class ASIN : public SFC {
 public:
  ASIN(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("ASIN");
  }

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);
};

}

#endif
