#ifndef PLC_EMULATOR_SFB_TOF_H_
#define PLC_EMULATOR_SFB_TOF_H_

#include "sfb.h"

namespace plc_emulator {
class TOF : public SFB {
 public:
  TOF(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("TOF");
  }

  void Execute(Variable *curr_result, Variable *sfb);
};

}

#endif //PLC_EMULATOR_SFB_TOF_H_
