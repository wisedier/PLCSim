#ifndef PLC_EMULATOR_MODULES_ACTUATOR_H_
#define PLC_EMULATOR_MODULES_ACTUATOR_H_
#include <string>
#include <unordered_map>
#include "config.h"
#include "module.h"

namespace plc_emulator {

// A generic actuator interface
class ActuatorModule : public Module {
 public:
  explicit ActuatorModule(const std::string &config_path)
      : Module(config_path) {};

  std::unique_ptr<VariableContainer> GetVariableContainer(
      int RamByteOffset, int RamBitOffset,
      std::string VariableDataTypeName) override {
    throw std::logic_error("Not Implemented");
  };

  std::unique_ptr<VariableContainer>
  GetVariableContainer(std::string AccessPath) override {
    throw std::logic_error("Not Implemented!");
  };

  std::unique_ptr<VariableContainer> GetVariableContainer(
      std::string resource_name,
      int mem_type,
      int byte_offset,
      int bit_offset,
      std::string var_data_type_name);

};

}

#endif //PLC_EMULATOR_MODULES_ACTUATOR_H_
