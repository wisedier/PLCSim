#ifndef PLC_EMULATOR__CLOCK_H_
#define PLC_EMULATOR__CLOCK_H_

#include <chrono>
#include <random>
#include <string>

namespace plc_emulator {
class ResourceImpl;

class Clock {
 private:
  double time_;
  bool is_virtual_;
  double expected_time_;
  ResourceImpl *associated_resource;
  std::default_random_engine generator;
  bool stop_;
 public:
  Clock(bool is_virtual, ResourceImpl *associated_resource);

  double GetCurrentTime() {
    if (is_virtual_) {
      return time_ / 1e+9;
    }
    time_ = (std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch())).count() / 1000.0;
    return time_;
  }

  void UpdateCurrentTime(double inc_amount);

  void UpdateCurrentTime(std::string ExecutedFn);

  void SleepFor(int sleep_duration_us);
};
}

#endif //PLC_EMULATOR__CLOCK_H_
