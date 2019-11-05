#ifndef PLC_EMULATOR__SYNCHRONIZED_QUEUE_H_
#define PLC_EMULATOR__SYNCHRONIZED_QUEUE_H_

#include <queue>
#include <condition_variable>

template<typename T>
class SynchronizedQueue {
 private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cond_var_;
  typedef std::lock_guard<std::mutex> lock;
  typedef std::unique_lock<std::mutex> ulock;
 public:
  void Push(T const &val) {
    lock l(mutex_);
    bool wake = queue_.empty();
    queue_.push(val);
    if (wake) {
      cond_var_.notify_one();
    }
  }

  T Pop() {
    ulock u(mutex_);
    while (queue_.empty()) {
      cond_var_.wait(u);
    }

    T retval = queue_.front();
    queue_.pop();
    return retval;
  }

  bool Empty() {
    return queue_.empty();
  }
};

#endif //PLC_EMULATOR__SYNCHRONIZED_QUEUE_H_
