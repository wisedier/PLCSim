#ifndef PLC_EMULATOR__POU_CONTAINER_H_
#define PLC_EMULATOR__POU_CONTAINER_H_

#include <string>
#include <utility>
#include <vector>
#include "datatype.h"
#include "config.h"

namespace plc_emulator {

class InstructionContainer {
 private:
  std::string name_;
  std::string label_;
  std::vector<std::string> operands;
  int pos_;

 public:
  InstructionContainer(std::string name, std::string label, int pos)
      : name_(std::move(name)), label_(std::move(label)), pos_(pos) {};

  void AddOperand(const std::string &operand) {
    operands.push_back(operand);
  }
};

class PouContainer {
 private:
  ConfigImpl *config_;
  DataType *pou_data_type_;
  ResourceImpl *resource_;
  bool initialized_;
  int instructions_count_;

  std::vector<std::unique_ptr<InstructionContainer>> instructions_;
  std::unordered_map<std::string, InstructionContainer *>
      insn_container_by_label;

 public:
  PouContainer(ConfigImpl *config, ResourceImpl *resource)
      : config_(config),
        resource_(resource),
        pou_data_type_(nullptr),
        initialized_(false),
        instructions_count_(0) {};

  void SetPouDataType(DataType *pou_data_type) {
    pou_data_type_ = pou_data_type;
    initialized_ = true;
  }

  PouContainer &AddInstruction(std::string instruction_string);

  int GetTotalNumberInstructions();

  InstructionContainer *GetInstruction(int pos);

  InstructionContainer *GetInstructionAt(std::string label);

  void Cleanup();
};
}

#endif //PLC_EMULATOR__POU_CONTAINER_H_
