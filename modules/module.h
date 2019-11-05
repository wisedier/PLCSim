#ifndef PLC_EMULATOR_MODULES_MODULE_H_
#define PLC_EMULATOR_MODULES_MODULE_H_

#define SUCCESS 1
#define PERM_DENIED -1
#define ERROR_NO_MEM -2

#include <config_interface.h>
#include "variable.h"

namespace plc_emulator {
// A helper class which restricts variable API
class VariableContainer {
 private:
  Variable *associated_variable_;
 public:
  explicit VariableContainer(Variable *associated_variable) :
      associated_variable_(associated_variable) {};

  DataType *GetDataTypeOfField(const std::string &nested_field_name) {
    DataTypeFieldAttributes attrs;
    associated_variable_->GetFieldAttributes(nested_field_name, attrs);
    return attrs.field.GetTypePtr();
  }

  template<typename T>
  T GetValueStoredAtField(std::string nested_field_name, int category) {
    return associated_variable_->GetValueStoredAtField<T>(nested_field_name,
                                                          category);
  }

  int SetField(const std::string &nested_field_name,
               const std::string &value,
               int count) {
    if (associated_variable_->GetAttributes().field.GetQualifier()
        == config::FieldQualifiers::READ_ONLY) {
      return PERM_DENIED;
    }

    if (!value.empty()
        || (count > associated_variable_->GetTotalSizeInBits() / 8)) {
      return ERROR_NO_MEM;
    }
    associated_variable_->SetField(nested_field_name, value, count);
    return SUCCESS;
  }

  int SetField(const std::string &nested_field_name, const std::string &value) {
    if (associated_variable_->GetAttributes().field.GetQualifier()
        == config::FieldQualifiers::READ_ONLY) {
      return PERM_DENIED;
    }

    associated_variable_->SetField(nested_field_name, value);
    return SUCCESS;
  }
};

class Module {
 protected:
  ConfigInterface config_if_;
 public:
  explicit Module(const std::string &config_path) : config_if_(config_path) {};

  DataType *GetDataType(const std::string &name) {
    return config_if_.LookupDataType(name);
  };

  virtual std::unique_ptr<VariableContainer>
  GetVariableContainer(std::string AccessPath) = 0;

  virtual std::unique_ptr<VariableContainer>
  GetVariableContainer(int mem_byte_offset,
                       int mem_bit_offset,
                       std::string var_data_type_name) = 0;

  virtual std::unique_ptr<VariableContainer>
  GetVariableContainer(std::string resource_name,
                       int mem_type,
                       int byte_offset,
                       int bit_offset,
                       std::string var_data_type_name) = 0;

  void Cleanup() { config_if_.Cleanup(); };

  uint8_t *GetPtrToRAMMemory() {
    return config_if_.GetPtrToMemory();
  };

  uint8_t *GetPtrToInputMemory(const std::string &resource_name) {
    return config_if_.GetPtrToInputMemory(resource_name);
  };

  uint8_t *GetPtrToOutputMemory(const std::string &ResourceName) {
    return config_if_.GetPtrToOutputMemory(ResourceName);
  };

  int GetMemSize() {
    return config_if_.GetMemSize();
  };

  int GetInputMemSize(const std::string &resource_name) {
    return config_if_.GetInputMemSize(resource_name);
  };

  int GetOutputMemSize(const std::string &resource_name) {
    return config_if_.GetOutputMemSize(resource_name);
  };

};
}

#endif //PLC_EMULATOR_MODULES_MODULE_H_
