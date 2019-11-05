#ifndef PLC_EMULATOR__DATATYPE_H_
#define PLC_EMULATOR__DATATYPE_H_

#include <string>
#include <cstdint>
#include <unordered_map>

#include "elementary_datatypes.h"
#include "config.pb.h"

namespace plc_emulator {
class DataType;
class Config;

class DataTypeField {
 private:
  std::string name_;
  std::string type_;
  int if_type_;
  config::DataTypeCategory category_;
  uint64_t range_min_;
  uint64_t range_max_;
  std::string initial_value_;
  DataType *type_ptr_;
  int qualifier_;
  std::string associated_resource_name_;
  int storage_mem_type_;
  int storage_byte_offset_;
  int storage_bit_offset_;
  std::string full_storage_spec_;
  std::string holding_pou_type_;
  int n_dimensions_;
  int dim1_;
  int dim2_;
 public:
  DataTypeField()
      : name_(""),
        type_(""),
        range_min_(0),
        range_max_(0),
        initial_value_(""),
        category_(static_cast<config::DataTypeCategory>(0)),
        if_type_(config::FieldInterfaceType::NA),
        type_ptr_(nullptr),
        qualifier_(config::FieldQualifiers::NONE),
        associated_resource_name_("NONE"),
        storage_mem_type_(-1),
        storage_byte_offset_(-1),
        storage_bit_offset_(-1),
        n_dimensions_(-1),
        dim1_(-1),
        dim2_(-1),
        full_storage_spec_("NONE"),
        holding_pou_type_("__NONE__") {};
  DataTypeField(std::string name,
                std::string type,
                config::DataTypeCategory category,
                int qualifier,
                uint64_t range_min,
                uint64_t range_max,
                std::string initial_value,
                int if_type,
                DataType *type_ptr,
                std::string resource_name = "NONE",
                std::string full_storage_spec = "NONE")
      : name_(std::move(name)),
        type_(std::move(type)),
        range_min_(range_min),
        range_max_(range_max),
        initial_value_(std::move(initial_value)),
        category_(category),
        if_type_(if_type),
        qualifier_(qualifier),
        type_ptr_(type_ptr),
        associated_resource_name_(std::move(resource_name)),
        storage_mem_type_(-1),
        storage_byte_offset_(-1),
        storage_bit_offset_(-1),
        n_dimensions_(-1),
        dim1_(-1),
        dim2_(-1),
        full_storage_spec_(std::move(full_storage_spec)),
        holding_pou_type_("__NONE__") {};

  std::string GetName() {
    return name_;
  }

  std::string GetType() {
    return type_;
  }

  int GetRangeMin() {
    return range_min_;
  }

  int GetRangeMax() {
    return range_max_;
  }

  std::string GetInitialValue() {
    return initial_value_;
  }

  config::DataTypeCategory GetCategory() {
    return category_;
  }

  int GetInterfaceType() {
    return if_type_;
  }

  int GetQualifier() {
    return qualifier_;
  }

  DataType *GetTypePtr() {
    return type_ptr_;
  }

  std::string GetAssociatedResourceName() {
    return associated_resource_name_;
  }

  int GetStorageMemType() {
    return storage_mem_type_;
  }

  int GetStorageByteOffset() {
    return storage_byte_offset_;
  }

  int GetStorageBitOffset() {
    return storage_bit_offset_;
  }

  std::string GetFullStorageSpec() {
    return full_storage_spec_;
  }

  int GetDimension() {
    return n_dimensions_;
  }

  int GetDimension(int dim) {
    return dim == 1 ? dim1_ : dim2_;
  }

  std::string GetHoldingPouType() {
    return holding_pou_type_;
  }

  void SetExplicitStorageConstraints(int mem_type,
                                     int byte_offset,
                                     int bit_offset);

  void Copy(DataTypeField &other) {
    name_ = other.GetName();
    type_ = other.GetType();
    range_min_ = other.GetRangeMin();
    range_max_ = other.GetRangeMax();
    initial_value_ = other.GetInitialValue();
    category_ = other.GetCategory();
    if_type_ = other.GetInterfaceType();
    qualifier_ = other.GetQualifier();
    type_ptr_ = other.GetTypePtr();
    storage_mem_type_ = other.GetStorageMemType();
    storage_byte_offset_ = other.GetStorageByteOffset();
    storage_bit_offset_ = other.GetStorageBitOffset();
    n_dimensions_ = other.GetDimension();
    dim1_ = other.GetDimension(1);
    dim2_ = other.GetDimension(2);
  }
};

class DataType {
 private:
  std::string alias_;
  std::string name_;
  Config *config_;
  std::unordered_map<int, std::vector<DataTypeField>> fields_by_if_type_;
  config::DataTypeCategory category_;
  int pou_type_;
  int size_in_bits_;
  int n_fields_;
  uint64_t range_min_;
  uint64_t range_max_;
  std::string initial_value_;
  std::vector<int> dim_size_;

  bool CheckRemFields(std::vector<std::string> &nested_fields,
                      int start_pos,
                      DataType *current);

  bool CheckRemFields(std::vector<std::string> &nested_fields,
                      int start_pos,
                      DataType *current,
                      DataTypeField &result);

  void SetElementaryDataTypeAttributes(std::string initial_value,
                                       uint64_t range_min,
                                       uint64_t range_max);

  bool GetDataFieldOfArrayElement(DataTypeField &defined_field,
                                  DataTypeField &result,
                                  int i,
                                  int j = -1);

 public:
  DataType(Config *config,
           std::string alias,
           std::string type,
           config::DataTypeCategory category = config::DataTypeCategory::NOT_ASSIGNED,
           std::string initial_value = "",
           uint64_t range_min = LLONG_MIN,
           uint64_t range_max = LLONG_MAX);

  DataType(Config *config,
           std::string alias,
           std::string type,
           int dim_size,
           config::DataTypeCategory category,
           std::string initial_value = "",
           uint64_t range_min = LLONG_MIN,
           uint64_t range_max = LLONG_MAX);

  DataType(Config *config,
           std::string alias,
           std::string type,
           int dim1,
           int dim2,
           config::DataTypeCategory category,
           std::string initial_value = "",
           uint64_t range_min = LLONG_MIN,
           uint64_t range_max = LLONG_MAX);

  std::string GetName() {
    return name_;
  }

  config::DataTypeCategory GetCategory() {
    return category_;
  }

  bool IsFieldPresent(std::string nested_field_name);

  DataType *LookupDataType(std::string name);

  void AddDataTypeField(std::string name,
                        std::string type,
                        int if_type,
                        int qualifier,
                        uint64_t range_min,
                        uint64_t range_max,
                        std::string full_storage_spec = "NONE");

  void AddDataTypeField(std::string name,
                        std::string type,
                        config::DataTypeCategory category,
                        std::string initial_value,
                        int if_type,
                        int qualifier,
                        uint64_t range_min,
                        uint64_t range_max,
                        std::string full_storage_spec = "NONE");

  void AddArrayDataTypeField(std::string name,
                             std::string type,
                             int dim_size,
                             std::string initial_value,
                             int if_type,
                             int qualifier,
                             uint64_t range_min,
                             uint64_t range_max,
                             std::string full_storage_spec = "NONE");

  void AddArrayDataTypeField(std::string name,
                             std::string type,
                             int dim1,
                             int dim2,
                             std::string initial_value,
                             int if_type,
                             int qualifier,
                             uint64_t range_min,
                             uint64_t range_max,
                             std::string full_storage_spec = "NONE");

  void AddDataTypeFieldAt(std::string name,
                          std::string type,
                          std::string initial_value,
                          int qualifier,
                          uint64_t range_min,
                          uint64_t range_max,
                          int mem_type,
                          int byte_offset,
                          int bit_offset,
                          std::string resource_name = "NONE",
                          std::string full_storage_spec = "NONE");

  void AddDataTypeFieldAt(std::string name,
                          std::string type,
                          config::DataTypeCategory category,
                          std::string initial_value,
                          int qualifier,
                          uint64_t range_min,
                          uint64_t range_max,
                          int mem_type,
                          int byte_offset,
                          int bit_offset,
                          std::string resource_name = "NONE",
                          std::string full_storage_spec = "NONE");

  void AddDataTypeFieldAt(std::string name,
                          std::string type,
                          int dim_size,
                          std::string initial_value,
                          int qualifier,
                          uint64_t range_min,
                          uint64_t range_max,
                          int mem_type,
                          int byte_offset,
                          int bit_offset,
                          std::string resource_name = "NONE",
                          std::string full_storage_spec = "NONE");

  void AddDataTypeFieldAt(std::string name,
                          std::string type,
                          int dim1,
                          int dim2,
                          std::string initial_value,
                          int qualifier,
                          uint64_t range_min,
                          uint64_t range_max,
                          int mem_type,
                          int byte_offset,
                          int bit_offset,
                          std::string resource_name = "NONE",
                          std::string full_storage_spec = "NONE");

  bool GetDataTypeField(std::string nested_field_name, DataTypeField &result);

  void Cleanup();
};

class DataTypeUtils {
 public:
  static bool ValueToBool(std::string value, bool &r);
  static bool ValueToByte(std::string value, uint8_t &r);
  static bool ValueToWord(std::string value, uint16_t &r);
  static bool ValueToDWord(std::string value, uint32_t &r);
  static bool ValueToQWord(std::string value, uint64_t &r);
  static bool ValueToChar(std::string value, char &r);
  static bool ValueToShort(std::string value, int16_t &r);
  static bool ValueToInt(std::string value, int32_t &r);
  static bool ValueToLongInt(std::string value, int64_t &r);
  static bool ValueToFloat(std::string value, float &r);
  static bool ValueToDouble(std::string value, double &r);
  static bool ValueToDate(std::string value, DateType &r);
  static bool ValueToTime(std::string value, TimeType &r);
  static bool ValueToDateTime(std::string value, DateTime &r);

  static bool BoolToAny(bool Value, int category, std::string &r);
  static bool ByteToAny(uint8_t Value, int category, std::string &r);
  static bool WordToAny(uint16_t Value, int category, std::string &r);
  static bool DWordToAny(uint32_t Value, int category, std::string &r);
  static bool QWordToAny(uint64_t Value, int category, std::string &r);
  static bool CharToAny(char Value, int category, std::string &r);
  static bool ShortToAny(int16_t Value, int category, std::string &r);
  static bool IntToAny(int32_t Value, int category, std::string &r);
  static bool LongIntToAny(int64_t Value, int category, std::string &r);
  static bool FloatToAny(float Value, int category, std::string &r);
  static bool DoubleToAny(double Value, int category, std::string &r);
  static bool TimeToAny(TimeType time_value, int category, std::string &r);

  static std::string DateTimeToString(DateTime &dt);
  static std::string DateToString(Date &date1);
  static void AddToDT(DateTime &Dt, TimeType &Time);
  static void AddToTOD(Time &tod, TimeType &Time);
  static void SubFromDT(DateTime &Dt, TimeType &Time);
  static void SubFromTOD(Time &tod, TimeType &Time);
  static TimeType SubDTs(DateTime &Dt1, DateTime &Dt2);
  static TimeType SubTODs(Time &tod1, Time &tod2);
  static TimeType SubDATEs(Date &date1, Date &date2);
};
}

#endif //PLC_EMULATOR__DATATYPE_H_
