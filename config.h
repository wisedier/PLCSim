#ifndef PLC_EMULATOR__CONFIG_H_
#define PLC_EMULATOR__CONFIG_H_

#include <memory>
#include <string>
#include <thread>
#include <unordered_map>

#include "config.pb.h"
#include "datatype_registry.h"
#include "logger.h"
#include "mem_unit.h"
#include "resource_registry.h"
#include "resource_manager.h"

namespace plc_emulator {
class Config {
 private:
  std::unique_ptr<DataTypeRegistry> registered_data_types_;
  ResourceRegistry *registered_resource_{};
  int mem_size_{};
  MemUnit memory_;
  std::string path_;
  std::string name_;
  config::Specification spec_;
  std::unique_ptr<Variable> global_pou_var_;
  std::unique_ptr<Variable> access_pou_var_;
  std::unordered_map<int, std::string> default_initial_values_;
  std::unordered_map<std::string, std::unique_ptr<Variable>> accessed_fields_;

  virtual void RegisterAllElementaryDataTypes() = 0;

  virtual void RegisterAllComplexDataTypes() = 0;

  virtual void RegisterAllResources() = 0;

 public:
  std::unique_ptr<Logger> logger;

  Config() = default;

  ~Config() = default;

  std::string GetName() {
    return name_;
  }

  virtual DataType *LookupDataType(std::string name) = 0;

  virtual Variable *GetExternalVariable(std::string nested_field_name) = 0;

  virtual Variable *GetPou(std::string name) = 0;

  virtual Variable *GetVariablePointerToMem(int byte_offset,
                                            int bit_offset,
                                            std::string var_data_type_name) = 0;

  virtual void Cleanup() = 0;
};

class ConfigImpl : public Config {
 private:
  int num_resources_;
  std::unordered_map<std::string, std::unique_ptr<ResourceManager>>
      resource_managers_;
  std::vector<std::thread> launched_resources_;
  bool stop_;
  bool enable_kronos_;
  float rel_cpu_speed_;
  int64_t per_round_inc_ns;

  void RegisterAllResources();

  void RegisterAllElementaryDataTypes();

  void RegisterAllComplexDataTypes();

  void InitializeAllPouVariables();
 public:
  Variable *GetExternalVariable(std::string nested_field_name);

  Variable *GetPOU(std::string name);

  Variable *GetAccessPathVariable(std::string access_path);

  DataType *LookupDataType(std::string name);

  ConfigImpl(std::string config_path,
             bool enable_kronos,
             long per_round_inc_ns = 1000000);

  Variable *GetVariablePointerToMem(int byte_offset, int bit_offset,
                                    std::string var_data_type_name);

  Variable *GetVariablePointerToResourceMem(std::string resource_name,
                                            int MemType,
                                            int byte_offset,
                                            int bit_offset,
                                            std::string var_data_type_name);

  void RunPlc();

  void LaunchPlc();

  void WaitForCompletion();

  void StopAllResources();

  void Cleanup();
};
}
#endif //PLC_EMULATOR__CONFIG_H_
