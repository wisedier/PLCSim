#ifndef PLC_EMULATOR_SFB_SFB_H_
#define PLC_EMULATOR_SFB_SFB_H_

#include <string>

#include "resource.h"

namespace plc_emulator {
class SFB {
 private:
  ResourceImpl *associated_resource_;
  std::string name_;
 public:
  void SetName(const std::string &name) {
    name_ = name;
  }

  void SetResource(ResourceImpl *resource) {
    associated_resource_ = resource;
  }

  virtual void Execute(Variable *curr_result, Variable *sfb) = 0;
};

}

#endif //PLC_EMULATOR_SFB_SFB_H_
