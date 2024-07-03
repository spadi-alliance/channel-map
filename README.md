# channel-map

Channel mapping library between Detector and Readout FEE

## Install

```sh
cmake -S . -B .build
cmake --build .build --target install
```

## Uninstall

```sh
xargs rm < .build/install_manifest.txt
rm -rf .build
```

## Usage


Add the following to your project's CMakeLists.txt.

```sh
list(APPEND CMAKE_PREFIX_PATH /path/to/channel-map)
find_package(ChannelMap REQUIRED)
target_link_libraries(YourProject ChannelMap::ChannelMap)
```

For Makefile, the following.

```make
chmap_config	= /path/to/channel-map/bin/chmap-config
CFLAGS			+= $(shell $(chmap_config) --include)
LDFLAGS			+= $(shell $(chmap_config) --libs)
```

In your code,

```cpp
#include <channel_map.hpp>

your_function()
{
  auto& channel_map = chmap::ChannelMap::get_instance();
  channel_map.initialize("foo.csv");
  {
    chmap::ChannelTuple detector(1, 2, 3, 4, 5);
    const auto& fe = channel_map.get("fe", detector);
    auto fe_id = std::get<chmap::number_t>(fe[0]);
    auto fe_ch = std::get<chmap::number_t>(fe[1]);
	...
  }
  {
    const auto& fe = channel_map.get("fe", {0, "a", 3, "x"});
    ...
  }
}
```

See also `skeleton.cpp` for implementation details.
