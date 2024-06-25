#include "channel_map.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "debug_print.hpp"
#include "index_tuple.hpp"
#include "stopwatch.hpp"

namespace cmap {

ChannelMap::ChannelMap()
  : m_null_tuple(),
    m_header(),
    m_element_type(),
    m_unique_types(),
    m_fe2det_map(),
    m_det2fe_map()
{
}

void
ChannelMap::debug_print() {
  for (const auto& p : m_fe2det_map) {
    DEBUG << p.first << " " << p.second << std::endl;
  }

  {
    Stopwatch stopwatch;
    IndexTuple det(170, 30, 0, 262, 0);
    const auto& fe = det_to_fe(det);
    DEBUG << "det : " << det
          << "-> fe : " << fe << std::endl;
  }

  {
    Stopwatch stopwatch;
    IndexTuple fe(30, 270, 0);
    const auto& det = fe_to_det(fe);
    DEBUG << "fe : " << fe
          << "-> det : " << det << std::endl;
  }
}

const IndexTuple&
ChannelMap::det_to_fe(const IndexTuple& det) const {
  auto itr = m_det2fe_map.find(det);
  if (itr != m_det2fe_map.end()) {
    return itr->second;
  } else {
    WARNING << "key not found : " << det << std::endl;
    return m_null_tuple;
  }
}

const IndexTuple&
ChannelMap::fe_to_det(const IndexTuple& fe) const {
  auto itr = m_fe2det_map.find(fe);
  if (itr != m_fe2det_map.end()) {
    return itr->second;
  } else {
    WARNING << "key not found : " << fe << std::endl;
    return m_null_tuple;
  }
}

void
ChannelMap::initialize(const std::filesystem::path& file_path) {
  if (file_path.extension() == ".csv") {
    initialize_from_csv(file_path.string());
  } else {
    ERROR << "anything other than 'csv' is currently unsupported" << std::endl;
  }
}

void
ChannelMap::initialize_from_csv(const std::string& file_path) {
  Stopwatch stopwatch;

  std::ifstream file(file_path);
  if (!file.is_open()) {
    std::cerr << "ERROR file open fail : " << file_path << std::endl;
    std::exit(1);
  }

  std::string line;
  if (std::getline(file, line)) {
    int i = 0;
    for (const auto& h : split_line(line)){
      if (std::count(m_header.begin(), m_header.end(), h) > 0) {
        ERROR << "found duplicate header : " << h << std::endl;
      }
      m_header.push_back(h);
      auto type = split_line(h, '.')[0];
      m_element_type.push_back(type);
      m_unique_types.insert(type);
    }
  }

  while (std::getline(file, line)) {
    auto tokens = split_line(line);
    if (tokens.size() != m_header.size()) {
      ERROR << "column size = " << tokens.size()
            << " does not match header size = " << m_header.size()
            << ", skip this line : " << line << std::endl;
      continue;
    }
    make_tuple(tokens);
  }
}

void
ChannelMap::make_tuple(const std::vector<std::string>& tokens) {
  std::map<std::string, IndexTuple> tuples;
  for (const auto& t : m_unique_types) {
    IndexTuple tuple;
    for (int i=0, n=tokens.size(); i<n; ++i) {
      if (m_element_type[i] != t) continue;
      tuple.push_back(parse_element(tokens[i]));
      tuple.set_title(m_header[i]);
    }
    tuples[t] = tuple;
    DEBUG << tuple << std::endl;
  }
  m_fe2det_map[tuples["fe"]] = tuples["detector"];
  m_det2fe_map[tuples["detector"]] = tuples["fe"];
}

std::vector<std::string>
ChannelMap::split_line(const std::string& str, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream iss(str);
  while (std::getline(iss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

}
