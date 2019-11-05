#ifndef PLC_EMULATOR__VARIABLE_H_
#define PLC_EMULATOR__VARIABLE_H_

#include <string>
#include <cstdint>
#include <unordered_map>
#include "datatype.h"
#include "mem_unit.h"

namespace plc_emulator {
class Config;
class Resource;
class Variable;

enum Ops {
  kAdd,
  kSub,
  kMul,
  kDiv,
  kMod,
  kAnd,
  kOr,
  kXor,
  kLs,
  kRs,
  kEq,
  kGt,
  kLt,
  kGe,
  kLe,
};

enum OpTypes {
  kRelational,
  kArithmetic,
  kBitwise,
};

typedef struct DataTypeFieldAttributes {
  std::string nested_field_name;
  uint64_t relative_offset;
  DataTypeField field;
  Variable *hold_variable_ptr;
  Variable *parent_variable_ptr;
} DataTypeFieldAttributes;

class Variable {
 private:
  int byte_offset_;
  int bit_offset_;
  int total_size_in_bits_;
  bool is_variable_content_type_a_ptr_;
  bool prev_value_;
  std::string name_;
  DataType *data_type_;
  MemUnit mem_loc_;
  Config *config;
  Resource *associated_resource;
  std::unordered_map<std::string, std::unique_ptr<Variable>> accessed_fields_;
  bool mem_allocated_;
  bool is_directly_represented_;
  bool is_temporary_;
  bool first_read_;
  bool first_return_;
  DataTypeFieldAttributes attrs_;

  void CopyToVariableFieldFromPointer(DataTypeFieldAttributes &attrs,
                                      Variable *from);

  void GetAndStoreValue(std::string nested_field_name,
                        void *value,
                        int copy_size,
                        int category);
  void CheckOperationValidity(int category, Ops var_op);

  template<typename T>
  bool ArithmeticOpOnVariables(T lhs, T rhs, int category, Ops var_op);

  template<typename T>
  bool RelationalOpOnVariables(T lhs, T rhs, int category, Ops var_op);

  template<typename T>
  bool BitwiseOpOnVariables(T lhs, T rhs, int category, Ops var_op);

  template<typename T>
  bool AllOpsOnVariables(T lhs, T rhs, int category, Ops var_op);

  void InitializeVariable(Variable *v, std::string initial_value);

  void InitializeAllNonPtrFields();

  void InitializeAllDirectlyRepresentedFields();

  void CheckValidity();

  void ParseRemFieldAttributes(std::vector<std::string> &fields,
                               int start_pos,
                               DataTypeFieldAttributes &attrs,
                               Variable *holder_variable,
                               DataType *current);

  void SafeMemRead(void *dst, MemUnit *from, int count, int offset);

  void SafeMemWrite(MemUnit *to, int count, int offset, void *src);

  void SafeBitWrite(MemUnit *to, int byte_offset, int bit_offset, bool value);

 public:
  Variable(Config *config,
           Resource *associated_resource,
           std::string name,
           std::string type);

  int GetByteOffset() {
    return byte_offset_;
  }

  int GetTotalSizeInBits() {
    return total_size_in_bits_;
  }

  DataType *GetDataType() {
    return data_type_;
  }

  MemUnit GetMemoryLocation() {
    return mem_loc_;
  }

  DataTypeFieldAttributes GetAttributes() {
    return attrs_;
  }

  void Cleanup();

  void AllocateStorage();

  void AllocateStorage(std::string shared_mem_file_path);

  void AllocateAndInitialize();

  void AllocateAndInitialize(std::string shared_mem_file_name);

  void ResolveAllExternalFields();

  void OnExecutorStartup();

  std::unique_ptr<Variable> GetCopy();

  void SetField(std::string nested_field_name, std::string value);

  void SetField(std::string nested_field_name, std::string value, int count);

  void SetField(std::string nested_field_name, Variable *from);

  Variable *GetPtrToField(std::string nested_field_name);

  template<typename T>
  T GetValueStoredAtField(std::string nested_field_name, int category);

  Variable *GetPtrStoredAtField(std::string nested_field_name);

  void GetFieldAttributes(std::string nested_field_name,
                          DataTypeFieldAttributes &attrs);

  bool InitiateOperationOnVariables(Variable &V, int VarOp);

  Variable &operator=(Variable &V);
  Variable &operator+(Variable &V);
  Variable &operator-(Variable &V);
  Variable &operator/(Variable &V);
  Variable &operator*(Variable &V);
  Variable &operator%(Variable &V);
  Variable &operator&(Variable &V);
  Variable &operator|(Variable &V);
  Variable &operator^(Variable &V);
  Variable &operator<<(Variable &V);
  Variable &operator>>(Variable &V);
  Variable &operator!();
  friend bool operator==(Variable &lhs, Variable &rhs) {
    int count = lhs.total_size_in_bits_ / 8;
    DataType *l_data_type = lhs.GetDataType();
    if (l_data_type == nullptr) {
      return false;
    }
    config::DataTypeCategory l_category = l_data_type->GetCategory();
    if (l_category == config::DataTypeCategory::ARRAY
        || l_category == config::DataTypeCategory::DERIVED
        || l_category == config::DataTypeCategory::POU) {
      if (lhs.GetTotalSizeInBits() != rhs.GetTotalSizeInBits()) {
        return false;
      }

      for (int i = 0; i < count; i++) {
        char *lhs_val = (char *) lhs.GetMemoryLocation().GetPointerToMemory(
            lhs.GetByteOffset() + i);
        char *rhs_val = (char *) rhs.GetMemoryLocation().GetPointerToMemory(
            rhs.GetByteOffset() + i);
        if (*lhs_val != *rhs_val) {
          return false;
        }
      }
      return true;
    }
    return lhs.InitiateOperationOnVariables(rhs, Ops::kEq);
  }

  friend bool operator>(Variable &lhs, Variable &rhs) {
    return lhs.InitiateOperationOnVariables(rhs, Ops::kGt);
  }

  friend bool operator>=(Variable &lhs, Variable &rhs) {
    return lhs.InitiateOperationOnVariables(rhs, Ops::kGe);
  }

  friend bool operator<(Variable &lhs, Variable &rhs) {
    return lhs.InitiateOperationOnVariables(rhs, Ops::kLt);
  }

  friend bool operator<=(Variable &lhs, Variable &rhs) {
    return lhs.InitiateOperationOnVariables(rhs, Ops::kLe);
  }
};
}

#endif //PLC_EMULATOR__VARIABLE_H_
