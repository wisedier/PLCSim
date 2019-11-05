#ifndef PLC_EMULATOR__RESOURCE_REGISTRY_H_
#define PLC_EMULATOR__RESOURCE_REGISTRY_H_

#include <memory>
#include <string>
#include <unordered_map>

#include "resource.h"

namespace plc_emulator {
class Resource;
class Config;

class ResourceRegistry {
 private:
  Config *config_;
  std::unordered_map<std::string, std::unique_ptr<Resource>> registry_;
 public:
  ResourceRegistry(Config *config) : config_(config) {};

  void RegisterResource(std::string resource_name,
                        std::unique_ptr<Resource> resource);

  Resource *GetResource(std::string resource_name);

  void Cleanup();
};
}

#endif //PLC_EMULATOR__RESOURCE_REGISTRY_H_
