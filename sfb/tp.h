#ifndef PLC_EMULATOR_SFB_TP_H_
#define PLC_EMULATOR_SFB_TP_H_

#include "sfb.h"

namespace plc_emulator {
class TP : public SFB {
 public:
  TP(ResourceImpl *associated_resource) {
    SetResource(associated_resource);
    SetName("TP");
  }

  void Execute(Variable *curr_result, Variable *sfb);
};

}

#endif //PLC_EMULATOR_SFB_TP_H_
