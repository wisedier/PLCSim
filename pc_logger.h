#ifndef PLC_EMULATOR__PC_LOGGER_H_
#define PLC_EMULATOR__PC_LOGGER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <utility>

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
    assert(LogLevel_IsValid(log_level));
    if (!log_file_.empty()) {
      ofs_.open(log_file_, std::ofstream::out | std::ofstream::app);
    }
  }
};
}

#endif //PLC_EMULATOR__PC_LOGGER_H_
