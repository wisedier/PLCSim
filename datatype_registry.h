#ifndef PLC_EMULATOR__DATATYPE_REGISTRY_H_
#define PLC_EMULATOR__DATATYPE_REGISTRY_H_

#include <iostream>
#include <unordered_map>

#include "datatype.h"

namespace plc_emulator {
class DataType;
class Config;

class DataTypeRegistry {
 private:
  Config *config_;
  std::unordered_map<std::string, std::unique_ptr<DataType>> registry_;
 public:
  DataTypeRegistry(Config *config) : config_(config) {};
  void RegisterDataType(std::string name, std::unique_ptr<DataType> data_type);
  DataType *GetDataType(std::string name);
  void GetAllRegisteredElementaryDataTypes(std::vector<DataType *> &elementary_data_types);
  void Cleanup();
};

}

#endif //PLC_EMULATOR__DATATYPE_REGISTRY_H_
