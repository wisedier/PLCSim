#ifndef PLC_EMULATOR_MODULES_COMMUNICATION_H_
#define PLC_EMULATOR_MODULES_COMMUNICATION_H_

#include <string>
#include <memory>
#include "module.h"
#include "variable.h"

namespace plc_emulator {

class CommunicationModule : public Module {
 public:
  CommunicationModule(const std::string &config_path) : Module(config_path) {};

  std::unique_ptr<VariableContainer> GetVariableContainer(
      int mem_byte_offset,
      int mem_bit_offset,
      std::string var_data_type_name);

  std::unique_ptr<VariableContainer> GetVariableContainer(
      std::string resource_name,
      int mem_type,
      int byte_offset,
      int bit_offset,
      std::string var_data_type_name) override {
    throw std::logic_error("Not Implemented");
  };

  std::unique_ptr<VariableContainer>
  GetVariableContainer(std::string nested_access_path);
};
}

#endif //PLC_EMULATOR_MODULES_COMMUNICATION_H_
