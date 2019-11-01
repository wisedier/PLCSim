#ifndef PLC_EMULATOR__MEM_UNIT_H_
#define PLC_EMULATOR__MEM_UNIT_H_

#include <iostream>
#include <memory>

extern "C" {
#include <semaphore.h>
};

namespace plc_emulator {
class MemUnit {
 private:
  std::shared_ptr<char> base_storage_location_;
  bool initialized_;
  int mem_unit_size_bytes_;
  bool is_mem_controller_active_;
  sem_t *sem_lock_;
  std::string sem_name_;
  std::string mmap_file_name_;
 public:
  MemUnit()
      : mem_unit_size_bytes_(0),
        initialized_(false),
        is_mem_controller_active_(false),
        sem_lock_(nullptr),
        mmap_file_name_("") {};

  void AllocateStaticMemory(int size_bytes);
  void AllocateSharedMemory(int size_bytes,
                            std::string mmap_file_path,
                            std::string lock_name);
  std::shared_ptr<char> GetStorageLocation();
  bool IsInitialized();
  int GetMemUnitSize();
  void SetMemUnitLocation(MemUnit *from);
  void *GetPointerToMemory(int offset);
  void CopyFromMemUnit(MemUnit *from,
                       int from_start_offset,
                       int copy_size_bytes,
                       int to_start_offset);
  void ReallocateStaticMemory(int mem_size);
  void Cleanup();
  friend bool operator==(const MemUnit &self, const MemUnit &other) {
    return self.base_storage_location_.get()
        == other.base_storage_location_.get();
  }
};
}

#endif //PLC_EMULATOR__MEM_UNIT_H_
