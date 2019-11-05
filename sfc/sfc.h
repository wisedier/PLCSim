#ifndef PLC_EMULATOR_SFC_SFC_H_
#define PLC_EMULATOR_SFC_SFC_H_

#include "resource.h"

namespace plc_emulator {

//! Generic abstract class for an IL SFC
class SFC {
 private:
  ResourceImpl *associated_resource_;
  std::string name_;
 public:
  void SetResource(ResourceImpl *resource) {
    associated_resource_ = resource;
  }

  void SetName(const std::string &name) {
    name_ = name;
  }

  virtual void Execute(Variable *curr_result, std::vector<Variable *> &ops) = 0;
};

}

#endif //PLC_EMULATOR_SFC_SFC_H_
