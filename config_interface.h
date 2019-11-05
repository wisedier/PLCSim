#ifndef PLC_EMULATOR__CONFIG_INTERFACE_H_
#define PLC_EMULATOR__CONFIG_INTERFACE_H_

#include <string>
#include <unordered_map>
#include <stdexcept>
#include "config.h"

namespace plc_emulator {

class ConfigInterface : public Config {
 private:
  int num_resources_;
  std::unordered_map<std::string, int> access_path_field_qualifier_;

  void RegisterAllElementaryDataTypes();

  void RegisterAllComplexDataTypes();

  void RegisterAllResources();
 public:
  ~ConfigInterface() {};

  ConfigInterface(std::string config_path);

  DataType *LookupDataType(std::string name);

  Variable *GetExternalVariable(std::string nested_field_name);

  Variable *GetVariablePointerToMem(int byte_offset,
                                    int bit_offset,
                                    std::string var_data_type_name);

  Variable *GetVariablePointerToResourceMem(std::string resource_name,
                                            int mem_type,
                                            int byte_offset,
                                            int bit_offset,
                                            std::string var_data_type_name);

  Variable *GetPou(std::string name) {
    throw std::logic_error("Not Implemented");
  };

  void Cleanup();

  uint8_t *GetPtrToMemory();

  uint8_t *GetPtrToInputMemory(std::string resource_name);

  uint8_t *GetPtrToOutputMemory(std::string ResourceName);

  int GetMemSize();

  int GetInputMemSize(std::string resource_name);

  int GetOutputMemSize(std::string resource_name);
};
}

#endif //PLC_EMULATOR__CONFIG_INTERFACE_H_
