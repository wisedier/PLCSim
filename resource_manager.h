#ifndef PLC_EMULATOR__RESOURCE_MANAGER_H_
#define PLC_EMULATOR__RESOURCE_MANAGER_H_

#include <syscall.h>

extern "C" {
#include "resource.h"
};

namespace plc_emulator {
class ResourceManager {
 private:
  ResourceImpl *associated_resource_;
  std::mutex _lock;
  pid_t resource_thread_pid_;
 public:
  ResourceManager(ResourceImpl *associated_resource) :
      associated_resource_(associated_resource) {
    resource_thread_pid_ = 0;
  };

  void set_tid() {
    std::lock_guard<std::mutex> l(_lock);
    resource_thread_pid_ = syscall(SYS_gettid);
  }

  pid_t get_tid() {
    while (true) {
      std::lock_guard<std::mutex> l(_lock);
      if (resource_thread_pid_ != 0)
        break;
    }
    return resource_thread_pid_;
  }
  void ExecuteResource();

  void ExecuteResourceManager();

  std::thread LaunchResource();

  std::thread LaunchResourceManager();
};
}

#endif //PLC_EMULATOR__RESOURCE_MANAGER_H_
