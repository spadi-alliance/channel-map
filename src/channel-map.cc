// -*- C++ -*-

#include "channel-map.hh"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "debug-print.hh"
#include "index-tuple.hh"
#include "stopwatch.hh"

namespace cmap
{
ChannelMap::ChannelMap()
  : m_header(),
    m_types()
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
    std::cerr << "ERROR file open fail : " << filepath << std::endl;
    std::exit(1);
  }

  std::string line;
  if (std::getline(file, line)) {
    int i = 0;
    for (const auto& h : SplitLine(line)){
      m_header.push_back(h);
      auto type = SplitLine(h, '.')[0];
      m_types.push_back(type);
      m_unique_types.insert(type);
    }
  }

  while (std::getline(file, line)) {
    auto tokens = SplitLine(line);
    const auto& tuple = MakeTuple(tokens);
  }
}

const IndexTuple*
ChannelMap::MakeTuple(const std::vector<std::string>& tokens) {
  for (const auto& t : m_unique_types) {
    DEBUG << t << " " << std::string(80, '=') << std::endl;
    IndexTuple tuple;
    for (int i=0, n=tokens.size(); i<n; ++i) {
      if (m_types[i] != t) continue;
      bool is_digit = false;
      try {
        std::size_t pos;
        std::stoull(tokens[i], &pos);
        is_digit = (pos == tokens[i].length());
      } catch (const std::invalid_argument&) {
        is_digit = false;
      // } catch (const std::out_of_range&) {
      //   is_digit = false;
      }
      element_t element;
      if (is_digit)
        element = std::stoull(tokens[i]);
      else
        element = tokens[i];
      tuple[m_header[i]] = element;
      // DEBUG << m_types[i] << "-" << m_header[i] << " : " << tokens[i] << " " << element << " (" << is_digit << ")" << std::endl;
    }
    DEBUG << tuple << std::endl;
  }
  return nullptr;
}

std::vector<std::string>
ChannelMap::SplitLine(const std::string& str, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream iss(str);
  while (std::getline(iss, token, delimiter)) {
    // DEBUG << "Token: " << token << std::endl;
    tokens.push_back(token);
  }
  return tokens;
}

}
