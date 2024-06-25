#ifndef CHANNELMAP_DEBUGPRINT_H_
#define CHANNELMAP_DEBUGPRINT_H_

#include <iostream>
#include <fstream>

namespace cmap {
std::ofstream devnull("/dev/null");
}

#ifdef DEBUG
#undef DEBUG
#define DEBUG std::cout << "DEBUG   " << __PRETTY_FUNCTION__ \
  << " L" << __LINE__ << "\n      "
#else
#define DEBUG cmap::devnull
#endif

#define INFO std::cout << "\033[0;34m" << "INFO    " << "\033[0m"
#define WARNING std::cout << "\033[0;33m" << "WARNING " << "\033[0m"
#define ERROR std::cerr << "\033[0;31m" << "ERROR   " << "\033[0m"

#endif
