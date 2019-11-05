#ifndef __PC_EMULATOR_INCLUDE_SFC_ANY_TO_ANY_H
#define __PC_EMULATOR_INCLUDE_SFC_ANY_TO_ANY_H

#include "sfc.h"

namespace plc_emulator {
class AnyToAny : public SFC {
 private:
  DataType *target_;
  DataType *src_;
 public:
  AnyToAny(ResourceImpl *associated_resource,
           DataType *target,
           DataType *src) {
    SetResource(associated_resource);
    target_ = target;
    src_ = src;

    std::string src_name = src->GetName();
    std::string sfc_name;

    switch (target_->GetCategory()) {
      case config::DataTypeCategory::BOOL:sfc_name = src_name + "_TO_BOOL";
        break;
      case config::DataTypeCategory::BYTE:sfc_name = src_name + "_TO_BYTE";
        break;
      case config::DataTypeCategory::WORD:sfc_name = src_name + "_TO_WORD";
        break;
      case config::DataTypeCategory::DWORD:sfc_name = src_name + "_TO_DWORD";
        break;
      case config::DataTypeCategory::QWORD:sfc_name = src_name + "_TO_LWORD";
        break;
      case config::DataTypeCategory::CHAR:sfc_name = src_name + "_TO_CHAR";
        break;
      case config::DataTypeCategory::SHORT:sfc_name = src_name + "_TO_SHORT";
        break;
      case config::DataTypeCategory::INT:sfc_name = src_name + "_TO_INT";
        break;
      case config::DataTypeCategory::LONG:sfc_name = src_name + "_TO_LONG";
        break;
      case config::DataTypeCategory::FLOAT:sfc_name = src_name + "_TO_FLOAT";
        break;
      case config::DataTypeCategory::DOUBLE:sfc_name = src_name + "_TO_DOUBLE";
        break;
      case config::DataTypeCategory::TIME:
        if (src_->GetCategory() == config::DataTypeCategory::DATETIME) {
          sfc_name = src_name + "DATETIME_TO_TIME";
        } else {
          associated_resource->GetConfig()->logger->Error(
              "Cannot create a type conversion sfc for complex data types");
          exit(EXIT_FAILURE);
        }
        break;
      case config::DataTypeCategory::DATE:
        if (src_->GetCategory() == config::DataTypeCategory::DATETIME) {
          sfc_name = src_name + "DATETIME_TO_DATE";
        } else {
          associated_resource->GetConfig()->logger->Error(
              "Cannot create a type conversion sfc for complex data types");
          exit(EXIT_FAILURE);
        }
        break;
      default:
        associated_resource->GetConfig()->logger->Error(
            "Cannot create a type conversion sfc for complex data types");
        exit(EXIT_FAILURE);
    }
    SetName(sfc_name);
  };

  void Execute(Variable *curr_result, std::vector<Variable *> &ops);

  Variable *Execute(Variable *curr_result, Variable *op);
};
}

#endif
