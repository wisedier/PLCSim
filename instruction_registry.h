#ifndef PLC_EMULATOR__INSTRUCTION_REGISTRY_H_
#define PLC_EMULATOR__INSTRUCTION_REGISTRY_H_

#include <string>

#include "instruction/instruction.h"
#include "config.h"
#include "resource.h"

namespace plc_emulator {
class InstructionRegistry {
 private:
  std::unordered_map<std::string, std::unique_ptr<Instruction>>
      instruction_registry_;
 public:
  InstructionRegistry(ResourceImpl *associated_resource);

  Instruction *GetInstruction(std::string name);
};
}

#endif //PLC_EMULATOR__INSTRUCTION_REGISTRY_H_
