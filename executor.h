#ifndef PLC_EMULATOR__EXECUTOR_H_
#define PLC_EMULATOR__EXECUTOR_H_

#include <vector>
#include <unordered_map>
#include "variable.h"
#include "pou_container.h"

namespace plc_emulator {
class Config;
class ResourceImpl;
class Task;

class Executor {
 private:
  ConfigImpl *config_;
  Variable *exec_pou_var_;
  ResourceImpl *associated_resource_;
  PouContainer *code_container_;
  bool initialized_;
  Task *associated_task_;

 public:
  Executor(ConfigImpl *config,
           ResourceImpl *associated_resource,
           Task *associated_task)
      : config_(config),
        exec_pou_var_(nullptr),
        associated_resource_(associated_resource),
        code_container_(nullptr),
        initialized_(false),
        associated_task_(associated_task) {};

  void SetExecPouVariable(Variable *exec_pou_var);

  void Run();

  void Cleanup();

  void RunInstruction(InstructionContainer &instruction_container);

  bool IsCrSet();

  void SaveCpuRegisters();

  void RestoreCpuRegisters();

  void ResetCpuRegisters();
};
}

#endif //PLC_EMULATOR__EXECUTOR_H_
