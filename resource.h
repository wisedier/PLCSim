#ifndef PLC_EMULATOR__RESOURCE_H_
#define PLC_EMULATOR__RESOURCE_H_

#include <string>
#include <utility>
#include <unordered_map>
#include <random>
#include "mem_unit.h"
#include "variable.h"
#include "synchronized_queue.h"
#include "pou_container.h"
#include "clock.h"
#include "task.h"

namespace plc_emulator {
class InstructionRegistry;
class SfcRegistry;
class SfbRegistry;

class Resource {
 private:
  int input_mem_size_{};
  int output_mem_size_{};
  MemUnit input_memory_;
  MemUnit output_memory_;
  std::unordered_map<std::string, std::unique_ptr<Variable>> resource_pou_vars_;
  std::unordered_map<std::string, std::unique_ptr<Variable>> accessed_fields_;
  std::string resource_name_;
  SynchronizedQueue<std::string> from_resource_manager_;
  SynchronizedQueue<std::string> to_resource_manager_;
 public:
  Resource() = default;;
  ~Resource() = default;;

  virtual void InitializeAllPouVars() = 0;

  virtual void OnStartUp() = 0;

  virtual Variable *GetExternalVariable(std::string nested_field_name) = 0;

  virtual Variable *GetVariablePointerToMem(int mem_type,
                                            int byte_offset,
                                            int bit_offset,
                                            std::string var_data_type_name) = 0;

  virtual void Cleanup() = 0;
};

class ResourceImpl {
 private:
  ConfigImpl *config_;
  std::unique_ptr<Clock> clock_;
  Variable *curr_result_;
  InstructionRegistry *insn_registry_;
  SfcRegistry *sfc_registry_;
  SfbRegistry *sfb_registry_;
  std::unordered_map<std::string,
                     std::unique_ptr<std::normal_distribution<double>>>
      exec_times_;
  std::unordered_map<std::string, std::unique_ptr<PouContainer>>
      code_containers_;
  std::unordered_map<std::string, std::unique_ptr<Task>> tasks_;
  Task *interval_task_;
  std::unordered_map<std::string, std::vector<Task *>> interrupt_tasks_;

  Variable *GetPouGlobalVariable(std::string nested_field_name);

  void RegisterPouVariable(std::string name, std::unique_ptr<Variable> var);
 public:
  ResourceImpl(ConfigImpl *config,
               std::string resource_name,
               int input_mem_size,
               int output_mem_size);

  ConfigImpl *GetConfig() {
    return config_;
  }

  void InitializeClock();

  void InitializeAllPouVars();

  void InitializeAllSfbVars();

  void ResolveAllExternalFields();

  void InitializeAllTasks();

  void OnStartup();

  void AddTask(std::unique_ptr<Task> Tsk);

  Task *GetTask(std::string TskName);

  Task *GetInterruptTaskToExecute();

  Task *GetIntervalTaskToExecuteAt(double schedule_time);

  void ExecuteInstruction(std::string name, std::vector<Variable *> &ops);

  void QueueTask(Task *task);

  Variable *GetExternVariable(std::string nested_field_name);

  Variable *GetPou(std::string name);

  Variable *GetVariablePointerToMem(int mem_type,
                                    int byte_offset,
                                    int bit_offset,
                                    std::string var_data_type_name);

  Variable *GetTmpVariable(std::string var_data_type_name,
                           std::string initial_value);

  Variable *GetVariableForImmediateOperand(std::string operand_value);

  PouContainer *CreateNewCodeContainer(DataType *pou_data_type);

  PouContainer *GetCodeContainer(std::string pou_data_type_name);

  void Cleanup();
};

class CompactTaskDescription {
 private:
  std::string task_name_;
  double next_schedule_time_ms_;

 public:
  CompactTaskDescription(std::string task_name, double next_schedule_time_ms)
      : task_name_(std::move(task_name)),
        next_schedule_time_ms_(next_schedule_time_ms) {};

  friend bool operator>(const CompactTaskDescription &lhs,
                        const CompactTaskDescription &rhs) {
    return lhs.next_schedule_time_ms_ > rhs.next_schedule_time_ms_;
  }

  friend bool operator>=(const CompactTaskDescription &lhs,
                         const CompactTaskDescription &rhs) {
    return lhs.next_schedule_time_ms_ >= rhs.next_schedule_time_ms_;
  }

  friend bool operator==(const CompactTaskDescription &lhs,
                         const CompactTaskDescription &rhs) {
    return lhs.next_schedule_time_ms_ == rhs.next_schedule_time_ms_;
  }

  friend bool operator<(const CompactTaskDescription &lhs,
                        const CompactTaskDescription &rhs) {
    return lhs.next_schedule_time_ms_ < rhs.next_schedule_time_ms_;
  }

  friend bool operator<=(const CompactTaskDescription &lhs,
                         const CompactTaskDescription &rhs) {
    return lhs.next_schedule_time_ms_ <= rhs.next_schedule_time_ms_;
  }
};
}

#endif //PLC_EMULATOR__RESOURCE_H_
