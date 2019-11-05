#ifndef PLC_EMULATOR__LOGGER_H_
#define PLC_EMULATOR__LOGGER_H_

#include <fstream>
#include <string>
#include <cassert>

#include "config.pb.h"

namespace plc_emulator {
class Config;

class Logger {
 private:
  Config *config_;
  std::string log_file_;
  int log_level_;
  std::ofstream ofs_;
 public:
  Logger(Config *config, std::string log_file, int log_level)
      : config_(config), log_file_(std::move(log_file)), log_level_(log_level) {
    assert(config::LogLevel_IsValid(log_level));
    if (!log_file_.empty()) {
      ofs_.open(log_file_, std::ofstream::out | std::ofstream::app);
    }
  }
  ~Logger() {
    if (ofs_.is_open()) {
      ofs_.close();
    }
  }

  void SetLevel(const int log_level);
  void Debug(const std::string message);
  void Info(const std::string message);
  void Warn(const std::string message);
  void Error(const std::string message);
  void Fatal(const std::string message);
  void Log(const std::string message);
};
}

#endif //PLC_EMULATOR__LOGGER_H_
