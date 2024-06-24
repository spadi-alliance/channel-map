#include "channel-map.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "debug-print.hpp"
#include "index-tuple.hpp"
#include "stopwatch.hpp"

namespace cmap {

ChannelMap::ChannelMap()
  : m_header(),
    m_types(),
    m_unique_types(),
    m_fe2det_map(),
    m_det2fe_map()
{
}

ChannelMap::~ChannelMap()
{
}

void
ChannelMap::DebugPrint()
{
  Stopwatch stopwatch;

  IndexTuple a;
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
      if (std::count(m_header.begin(), m_header.end(), h) > 0) {
        ERROR << "found duplicate header : " << h << std::endl;
      }
      m_header.push_back(h);
      auto type = SplitLine(h, '.')[0];
      m_types.push_back(type);
      m_unique_types.insert(type);
    }
  }

  while (std::getline(file, line)) {
    auto tokens = SplitLine(line);
    if (tokens.size() != m_header.size()) {
      ERROR << "column size = " << tokens.size()
            << " does not match header size = " << m_header.size()
            << ", skip this line : " << line << std::endl;
      continue;
    }
    MakeTuple(tokens);
  }
}

void
ChannelMap::MakeTuple(const std::vector<std::string>& tokens) {
  // std::vector<IndexTuple> tuples;
  std::map<std::string, IndexTuple> tuples;
  for (const auto& t : m_unique_types) {
    IndexTuple tuple;
    // tuple.Type(t);
    for (int i=0, n=tokens.size(); i<n; ++i) {
      if (m_types[i] != t) continue;
      bool is_number = false;
      try {
        std::size_t pos;
        std::stoull(tokens[i], &pos);
        is_number = (pos == tokens[i].length());
      } catch (const std::invalid_argument&) {
        is_number = false;
      } catch (const std::out_of_range&) {
        is_number = false;
      }
      element_t element;
      if (is_number) {
        element = std::stoull(tokens[i]);
      } else {
        element = tokens[i];
      }
      // DEBUG << i << " " << m_header[i] << " " << tokens[i]
      //       << " " << (is_number ? "(number)" : "(string)")
      //       << std::endl;
      // DEBUG << m_header[i] << " " << element << std::endl;
      tuple[m_header[i]] = element;
    }
    INFO << tuple << std::endl;
    // tuples.push_back(tuple);
    tuples[t] = tuple;
  }

  // m_tuple_set.insert(tuples);
  m_fe2det_map[tuples["fe"]] = tuples["detector"];
  m_det2fe_map[tuples["detector"]] = tuples["fe"];
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
