#ifndef PLC_EMULATOR__FUNCTIONS_REGISTRY_H_
#define PLC_EMULATOR__FUNCTIONS_REGISTRY_H_

#include <unordered_map>
#include <string>
#include <memory>

#include "variable.h"

namespace plc_emulator {
class ResourceImpl;
class FunctionsRegistry {
 private:
  std::unordered_map<std::string, std::unique_ptr<Variable>> function_registry_;
  ResourceImpl *associated_resource_;
 public:
  FunctionsRegistry(ResourceImpl *associated_resource);

  Variable *GetFunction(std::string name);
};
}

#endif //PLC_EMULATOR__FUNCTIONS_REGISTRY_H_
