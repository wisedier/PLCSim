#ifndef PLC_EMULATOR_MODULES_SENSOR_H_
#define PLC_EMULATOR_MODULES_SENSOR_H_

#include <string>
#include <memory>
#include <stdexcept>
#include "module.h"
#include "variable.h"

namespace plc_emulator {

class SensorModule : public Module {
 public:
  explicit SensorModule(const std::string &config_path)
      : Module(config_path) {};

  std::unique_ptr<VariableContainer> GetVariableContainer(
      int mem_byte_offset,
      int mem_bit_offset,
      std::string var_data_type_name) override {
    throw std::logic_error("Not Implemented");
  };
  std::unique_ptr<VariableContainer>
  GetVariableContainer(std::string AccessPath) override {
    throw std::logic_error("Not Implemented");
  };

  std::unique_ptr<VariableContainer> GetVariableContainer(
      std::string resource_name,
      int mem_type,
      int byte_offset,
      int bit_offset,
      std::string var_data_type_name);

};

}

#endif //PLC_EMULATOR_MODULES_SENSOR_H_
