#ifndef PLC_EMULATOR__RESOURCE_INTERFACE_H_
#define PLC_EMULATOR__RESOURCE_INTERFACE_H_

#include <string>
#include "resource.h"

namespace plc_emulator {
class ConfigInterface;

class ResourceInterface : public Resource {
 private:
  ConfigInterface *config_if_;
  std::string resource_name_;

  Variable *GetPouVariable(std::string name);

  Variable *GetPouGlobalVariable(std::string nested_field_name);

  void RegisterPouVariable(std::string name, std::unique_ptr<Variable> var);

  void InitializeAllSfbVars();

 public:
  ~ResourceInterface() {};

  ResourceInterface(ConfigInterface *config_if,
                    std::string resource_name,
                    int input_mem_size,
                    int output_mem_size);

  void InitializeAllPoUVars();

  void OnStartup();

  Variable *GetExternalVariable(std::string nested_field_name);

  Variable *GetPouFieldVariable(std::string nested_pou_field_name);

  Variable *GetVariablePointerToMem(int mem_type,
                                    int byte_offset,
                                    int bit_offset,
                                    std::string var_data_type_name);

  void Cleanup();
};

}

#endif //PLC_EMULATOR__RESOURCE_INTERFACE_H_
