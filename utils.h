#ifndef PLC_EMULATOR__UTILS_H_
#define PLC_EMULATOR__UTILS_H_

#include <string>
#include <vector>
#include <unordered_map>

extern "C" {
#include <fcntl.h>
#include <sys/mman.h>
};

#include "config.pb.h"
#include "system_specification.pb.h"

namespace plc_emulator {
class DataType;
class Variable;
class Config;
struct DataTypeFieldAttributes;

class Utils {
 public:
  static void InitializeDataType(Config *config,
                                 DataType *new_data_type,
                                 const config::DataType &data_type_spec);

  static void InitializeAccessDataType(Config *config,
                                       DataType *new_data_type,
                                       config::DataType &data_type_spec);

  static bool ExtractFromStorageSpec(std::string storage_spec,
                                     int *mem_type,
                                     int *byte_offset,
                                     int *bit_offset);

  static std::string GetElementaryDataTypeName(config::DataTypeCategory category);

  static int GetOpType(int var_op);

  static bool ExtractFromAccessStorageSpec(Config *config,
                                           std::string storage_spec,
                                           int *mem_type,
                                           int *byte_offset,
                                           int *bit_offset,
                                           std::string &candidate_resource_name);

  static std::string GetInstallationDirectory();

  static std::string ResolveAlias(std::string alias, Config *config);

  static std::string Getinitial_valueForArrayIdx(int i,
                                                 std::string initial_value,
                                                 DataType *element_data_type,
                                                 Config *config);

  static bool TestEqPointers(Variable *p, Variable *q);

  static bool IsFieldTypePtr(int if_type);

  static void ValidatePOUDefinition(Variable *pou_var, Config *config);

  static bool FileExists(const char *filename);

  static char *MakeSharedMmap(int n_elements, std::string filename);

  static Variable *GetVariable(std::string nested_field_name,
                               Config *config);

  static bool GetFieldAttributesForAccessPath(std::string access_path,
                                              Config *configuration,
                                              struct DataTypeFieldAttributesStruct &attrs);

  static bool ReadAccessCheck(Config *configuration,
                              std::string calling_pou_type,
                              std::string nested_field_name);

  static bool WriteAccessCheck(Config *configuration,
                               std::string calling_pou_type,
                               std::string nested_field_name);

  static Variable *ReallocateTmpVariable(Config *configuration,
                                         Variable *var,
                                         DataType *new_data_type,
                                         std::string initial_value);

  static Variable *BoolToAny(Config *configuration,
                             Variable *var, DataType *new_datatype);

  static Variable *ByteToAny(Config *configuration,
                             Variable *var, DataType *new_datatype);

  static Variable *WordToAny(Config *configuration,
                             Variable *var, DataType *new_datatype);

  static Variable *DWordToAny(Config *configuration,
                              Variable *var, DataType *new_datatype);

  static Variable *QWordToAny(Config *configuration,
                              Variable *var, DataType *new_datatype);

  static Variable *CharToAny(Config *configuration,
                             Variable *var, DataType *new_datatype);

  static Variable *ShortToAny(Config *configuration,
                              Variable *var, DataType *new_datatype);

  static Variable *IntToAny(Config *configuration,
                            Variable *var, DataType *new_datatype);

  static Variable *LongToAny(Config *configuration,
                             Variable *var, DataType *new_datatype);

  static Variable *FloatToAny(Config *configuration,
                              Variable *var, DataType *new_datatype);

  static Variable *DoubleToAny(Config *configuration,
                               Variable *var, DataType *new_datatype);

  static Variable *TimeToAny(Config *configuration,
                             Variable *var, DataType *new_datatype);

  static Variable *DateTimeToTime(Config *configuration,
                                  Variable *var, DataType *new_datatype);

  static Variable *DateTimeToDate(Config *configuration,
                                  Variable *var, DataType *new_datatype);

  static bool IsNumType(DataType *data_type);

  static bool IsBitType(DataType *data_type);

  static bool IsRealType(DataType *data_type);

  static bool SameClassOfDataTypes(DataType *DT1, DataType *DT2);

  static DataType *GetMostAppropriateTypeCast(Variable *Cr,
                                              std::vector<Variable *> &ops);

  static bool GenerateFullSpecification(
      std::string system_spec_path,
      config::Specification &full_specification);

  static bool IsOperandImmediate(std::string op);

  static void ExtractCallInterfaceMapping(
      std::unordered_map<std::string, std::string> &vars_to_set,
      std::unordered_map<std::string, std::string> &vars_to_get,
      std::string full_if_name);
};
}

#endif 
