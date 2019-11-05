#ifndef PLC_EMULATOR__SFC_REGISTRY_H_
#define PLC_EMULATOR__SFC_REGISTRY_H_

#include <unordered_map>
#include <string>
#include <memory>
#include "sfc/sfc.h"

namespace plc_emulator {

//! Class which registers and tracks all valid SFCs
class SfcRegistry {
 private:
  std::unordered_map<std::string, std::unique_ptr<SFC>> sfc_;
 public:
  SfcRegistry(ResourceImpl *associated_resource);

  SFC *GetSfc(std::string name);
};
}

#endif //PLC_EMULATOR__SFC_REGISTRY_H_
