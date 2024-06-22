#ifndef CHANNELMAP_STOPWATCH_H_
#define CHANNELMAP_STOPWATCH_H_

#include <chrono>

#include "debug-print.hpp"

namespace cmap {
class Stopwatch {
public:
  using clock = std::chrono::high_resolution_clock;
  using time_point = std::chrono::time_point<clock>;
  // using nanoseconds = std::chrono::nanoseconds;
  // using milliseconds = std::chrono::milliseconds;
  // using seconds = std::chrono::seconds;

  Stopwatch() : running(false) {
#ifdef DEBUG
    Start();
#endif
  }

  ~Stopwatch() {
#ifdef DEBUG
    Stop();
#endif
  }

  void Start() {
    start_time = clock::now();
    running = true;
  }

  void Stop() {
    if (running) {
      end_time = clock::now();
      running = false;
      Elapsed();
    }
  }

  template<typename Duration=std::chrono::nanoseconds>
  double Elapsed() const {
    auto end = running ? clock::now() : end_time;
    auto elapsed = std::chrono::duration_cast<Duration>(end - start_time).count();
    DEBUG << elapsed // << " / " << Duration::period::den
          << std::endl;
    return elapsed;
  }

private:
  time_point start_time;
  time_point end_time;
  bool running;
};

}

#endif
