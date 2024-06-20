// -*- C++ -*-

#include "ChannelMap.hxx"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace cmap
{

ChannelMap::ChannelMap()
{
}

ChannelMap::~ChannelMap()
{
}

void
ChannelMap::debugPrint()
{
}

void
ChannelMap::initializeFromCSV(const std::string& filepath)
{
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filepath << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string token;

    std::vector<std::string> tokens;
    while (std::getline(ss, token, ',')) {
      tokens.push_back(token);
    }

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
  }

}

}
