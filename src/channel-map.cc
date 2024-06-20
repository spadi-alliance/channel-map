// -*- C++ -*-

#include "channel-map.hh"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "debug-print.hh"
#include "index-tuple.hh"
#include "stopwatch.hh"

namespace
{
}

namespace cmap
{
ChannelMap::ChannelMap()
  : headers_(),
    types_()
{
}

ChannelMap::~ChannelMap()
{
}

void
ChannelMap::DebugPrint()
{
}

void
ChannelMap::InitializeFromCSV(const std::string& filepath)
{
  Stopwatch stopwatch;

  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filepath << std::endl;
    return;
  }

  std::string line;

  if (std::getline(file, line)) {
    headers_ = SplitLine(line);
  }

  while (std::getline(file, line)) {
    std::vector<std::string> tokens = SplitLine(line);

    // if (tokens.size() >= 2) {
    //   elnum_t number = std::stoul(tokens[0]);
    //   std::string str = tokens[1];
    //   MapElement element(number);
    //   {
    //     // std::lock_guard<std::mutex> lock(manager_mutex);
    //     elements[number] = element;
    //     MapElement::f_str2int_table[str] = number;
    //     MapElement::f_int2str_table[number] = str;
    //   }
    // }
    // DEBUG << line << std::endl;
  }

}

std::vector<std::string>
ChannelMap::SplitLine(const std::string& str, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream iss(str);
  while (std::getline(iss, token, delimiter)) {
    DEBUG << "Token: " << token << std::endl;
    tokens.push_back(token);
  }
  return tokens;
}

}
