#ifndef PLC_EMULATOR_SFB_TON_H_
#define PLC_EMULATOR_SFB_TON_H_

#include "sfb.h"

namespace plc_emulator {
class TON : public SFB {
 public:
  TON(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("TON");
  }

  void Execute(Variable *curr_result, Variable *sfb);
};

}

#endif //PLC_EMULATOR_SFB_TON_H_
