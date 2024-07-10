#ifndef CHANNELMAP_DEBUGPRINT_H_
#define CHANNELMAP_DEBUGPRINT_H_

#include <iostream>
#include <memory>
#include <sstream>

namespace chmap {
std::ofstream devnull("/dev/null");

enum class LogLevel { kDEBUG, kINFO, kWARNING, kERROR };

class LogBuffer : public std::stringbuf {
public:
  LogBuffer(LogLevel level) : m_level(level) {}

  int sync() override {
    std::cout << level_name() << "\033[0m" << str();
    str("");
    return 0;
  }

private:
  const char* level_name() {
    switch (m_level) {
    case LogLevel::kDEBUG: return "\033[0;32mDEBUG   ";
    case LogLevel::kINFO: return "\033[0;34mINFO    ";
    case LogLevel::kWARNING: return "\033[0;33mWARNING ";
    case LogLevel::kERROR: return "\033[0;31mERROR   ";
    default: return "";
    }
  }

  LogLevel m_level;
};

class LogStream : public std::ostream {
public:
  LogStream(LogLevel level)
    : std::ostream(m_buffer.get()),
      m_buffer(std::make_unique<LogBuffer>(level))
  {}

private:
  std::unique_ptr<LogBuffer> m_buffer;
};

#ifdef DEBUG
LogStream debug(LogLevel::kDEBUG);
#else
std::ostream debug("/dev/null");
#endif
LogStream info(LogLevel::kINFO);
LogStream warning(LogLevel::kWARNING);
LogStream error(LogLevel::kERROR);

}

#endif
