#ifndef PLC_EMULATOR__TASK_H_
#define PLC_EMULATOR__TASK_H_

#include <string>

#include "config.pb.h"
#include "executor.h"
#include "functions_registry.h"
#include "logger.h"
#include "variable.h"

namespace plc_emulator {

class ProgramContainer {
 private:
  std::string name_;
  ResourceImpl *associated_resource_;
  Variable *exec_pou_var_;
  std::unique_ptr<Executor> associated_executor_;
  std::vector<config::ProgramVariableInitialization> initialization_map_;
  Task *associated_task;
 public:
  ProgramContainer(ResourceImpl *associated_resource,
                   const config::ProgramSpecification &program_spec,
                   Task *associated_task);

  void Cleanup();
};

class Task {
 private:
  std::string name_;
  int priority_;
  config::TaskType type;
  int interval_ms_;
  ConfigImpl *config_;
  ResourceImpl *associated_resource_;
  Variable *Cr_;
  std::string trigger_var_name_;
  bool prev_trigger_var_value;
  bool ready_;
  bool executing_;
  double next_schedule_time_ms_;
  std::vector<std::unique_ptr<ProgramContainer>> associated_programs_;
  FunctionsRegistry *fc_registry_;

 public:
  Task(ConfigImpl *config,
       ResourceImpl *associated_resource,
       const config::IntervalTaskSpecification &task_spec);

  Task(ConfigImpl *config,
       ResourceImpl *associated_resource,
       const config::InterruptTaskSpecification &task_spec);

  void SetNextScheduleTime(double next_schedule_time_ms) {
    next_schedule_time_ms_ = next_schedule_time_ms;
  };

  void AddProgramToTask(const config::ProgramSpecification &program_spec);

  void Execute();

  void Cleanup();
};
}

#endif //PLC_EMULATOR__TASK_H_
