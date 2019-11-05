#ifndef PLC_EMULATOR__SFB_REGISTRY_H_
#define PLC_EMULATOR__SFB_REGISTRY_H_

#include <unordered_map>
#include <memory>
#include <string>

#include "sfb/sfb.h"

namespace plc_emulator {
class SfbRegistry {
 private:
  std::unordered_map<std::string, std::unique_ptr<SFB>> sfb_;
 public:
  SfbRegistry(ResourceImpl *AssociatedResource);

  SFB *GetSFB(std::string SFBName);
};
}

#endif //PLC_EMULATOR__SFB_REGISTRY_H_
