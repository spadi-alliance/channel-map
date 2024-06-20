#ifndef CHANNELMAP_DEBUGPRINT_H_
#define CHANNELMAP_DEBUGPRINT_H_

#include <iostream>

#ifdef DEBUG
#undef DEBUG
#define DEBUG std::cout << "DEBUG " << __PRETTY_FUNCTION__ \
  << " L" << __LINE__ << "\n      "
#else
#define DEBUG std::ofstream("/dev/null")
#endif

#endif
