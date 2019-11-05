#ifndef PLC_EMULATOR_GRPC_API_H_
#define PLC_EMULATOR_GRPC_API_H_

#include "config_interface.h"

namespace plc_emulator {

class InterfaceAPI {
 public:
  ConfigInterface config_if;
  explicit InterfaceAPI(const std::string &config_path)
      : config_if(config_path) {};

  void SetSensorInput(
      std::string resource_name,
      int mem_type,
      int byte_offset,
      int bit_offset,
      std::string var_data_type_name,
      std::string Value);

  std::string GetActuatorOutput(
      std::string resource_name,
      int mem_type,
      int byte_offset,
      int bit_offset,
      std::string var_data_type_name);
};

}

#endif //PLC_EMULATOR_GRPC_API_H_
