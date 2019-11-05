//
// Created by bdev on 11/4/19.
//

#ifndef PLC_EMULATOR__ELEMENTARY_DATATYPES_H_
#define PLC_EMULATOR__ELEMENTARY_DATATYPES_H_

namespace plc_emulator {
struct BaseType {
  BaseType &operator+(const BaseType &rhs) {
    return *this;
  }

  BaseType &operator-(const BaseType &rhs) {
    return *this;
  }

  BaseType &operator/(const BaseType &rhs) {
    return *this;
  }

  BaseType &operator%(const BaseType &rhs) {
    return *this;
  }

  BaseType &operator*(const BaseType &rhs) {
    return *this;
  }

  BaseType &operator&(const BaseType &rhs) {
    return *this;
  }

  BaseType &operator|(const BaseType &rhs) {
    return *this;
  }

  friend bool operator>(const BaseType &lhs, const BaseType &rhs) {
    return false;
  }

  friend bool operator>=(const BaseType &lhs, const BaseType &rhs) {
    return false;
  }

  friend bool operator==(const BaseType &lhs, const BaseType &rhs) {
    return false;
  }

  friend bool operator<(const BaseType &lhs, const BaseType &rhs) {
    return false;
  }

  friend bool operator<=(const BaseType &lhs, const BaseType &rhs) {
    return false;
  }
};

struct DateType : BaseType {
  int year;
  int month;
  int day;

  friend bool operator>(const DateType &lhs, const DateType &rhs) {
    return lhs.year > rhs.year ||
        (lhs.year == rhs.year && lhs.month > rhs.month) ||
        (lhs.year == rhs.year && lhs.month == rhs.month
            && lhs.day > rhs.day);
  }

  friend bool operator>=(const DateType &lhs, const DateType &rhs) {
    return lhs.year > rhs.year ||
        (lhs.year == rhs.year && lhs.month > rhs.month) ||
        (lhs.year == rhs.year && lhs.month == rhs.month
            && lhs.day >= rhs.day);
  }

  friend bool operator==(const DateType &lhs, const DateType &rhs) {
    return (lhs.year == rhs.year && lhs.month == rhs.month
        && lhs.day == rhs.day);
  }

  friend bool operator<(const DateType &lhs, const DateType &rhs) {
    return lhs.year < rhs.year ||
        (lhs.year == rhs.year && lhs.month < rhs.month) ||
        (lhs.year == rhs.year && lhs.month == rhs.month
            && lhs.day < rhs.day);
  }

  friend bool operator<=(const DateType &lhs, const DateType &rhs) {
    return lhs.year < rhs.year ||
        (lhs.year == rhs.year && lhs.month < rhs.month) ||
        (lhs.year == rhs.year && lhs.month == rhs.month
            && lhs.day <= rhs.day);
  }
};

typedef DateType Date;

struct TimeType : BaseType {
  int hour;
  int minute;
  int second;

  [[nodiscard]] int TotalSeconds() const {
    return hour * 3600 + minute * 60 + second;
  }

  TimeType &operator+(const TimeType &rhs) {
    int total_seconds = this->TotalSeconds() + rhs.TotalSeconds();
    hour = total_seconds / 3600;
    minute = (total_seconds % 3600) / 60;
    second = total_seconds % 60;
    return *this;
  }

  TimeType &operator-(const TimeType &rhs) {
    int total_seconds = this->TotalSeconds() - rhs.TotalSeconds();
    hour = total_seconds / 3600;
    minute = (total_seconds % 3600) / 60;
    second = total_seconds % 60;
    return *this;
  }

  friend bool operator>(const TimeType &lhs, const TimeType &rhs) {
    return lhs.TotalSeconds() > rhs.TotalSeconds();
  }

  friend bool operator>=(const TimeType &lhs, const TimeType &rhs) {
    return lhs.TotalSeconds() >= rhs.TotalSeconds();
  }

  friend bool operator==(const TimeType &lhs, const TimeType &rhs) {
    return lhs.TotalSeconds() == rhs.TotalSeconds();
  }

  friend bool operator<(const TimeType &lhs, const TimeType &rhs) {
    return lhs.TotalSeconds() < rhs.TotalSeconds();
  }

  friend bool operator<=(const TimeType &lhs, const TimeType &rhs) {
    return lhs.TotalSeconds() <= rhs.TotalSeconds();
  }
};

typedef TimeType Time;

struct DateTimeType : BaseType {
  Date date;
  Time time;

  friend bool operator>(const DateTimeType &lhs, const DateTimeType &rhs) {
    return lhs.date > rhs.date || (lhs.date == rhs.date && lhs.time > rhs.time);
  }

  friend bool operator>=(const DateTimeType &lhs, const DateTimeType &rhs) {
    return lhs.date > rhs.date
        || (lhs.date == rhs.date && lhs.time >= rhs.time);
  }

  friend bool operator==(const DateTimeType &lhs, const DateTimeType &rhs) {
    return (lhs.date == rhs.date && lhs.time == rhs.time);
  }

  friend bool operator<(const DateTimeType &lhs, const DateTimeType &rhs) {
    return lhs.date < rhs.date || (lhs.date == rhs.date && lhs.time < rhs.time);
  }

  friend bool operator<=(const DateTimeType &lhs, const DateTimeType &rhs) {
    return lhs.date < rhs.date
        || (lhs.date == rhs.date && lhs.time <= rhs.time);
  }
};

typedef DateTimeType DateTime;

}

#endif //PLC_EMULATOR__ELEMENTARY_DATATYPES_H_
