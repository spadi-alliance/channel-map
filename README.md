# channel-map

Channel mapping library between Detector and Readout FEE

## Install

Build channel-map.

```sh
cmake -S . -B .build
cmake --build .build --target install
```

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

## Uninstall

```sh
xargs rm < .build/install_manifest.txt
rm -rf .build
```

## Parameter format

Only CSV is supported.
Write the element title of each column in the heading line.
Titles are classified into *Readout FEE* or *Detector* tuples using the first dot-delimited string.

Elements can be numbers or strings.
Prefixes such as `0xff`, `0b101`, `077`, etc. are interpreted as hexadecimal, binary, or octal numbers, respectively.
If they cannot be interpreted as numbers, they are assumed to be strings.

```test.csv
fe.node,fe.channel,fe.data,detector.id,detector.plane,detector.segment,detector.channel,detector.data
30,262,adc,170,30,0,262,0
30,263,0,170,30,0,263,0
30,264,0,170,30,0,264,0
30,265,0,170,30,0,265,0
30,266,0,170,30,0,266,0
30,267,0,170,30,0,267,0
30,268,0,170,30,0,268,0
30,269,0,170,30,0,269,0xff
30,270,0,170,30,0,270,A
30,271,0,170,30,0,271,C
```

## Usage

Initialize the singleton instance of the `ChannelMap` class
and use the `get` method to get a tuple from *FE* to *Detector* or the other way around.

`std::get<T>` returns the value if the specified type T matches the current type of `std::variant`,
otherwise it throws a `std::bad_variant_access` exception.

`std::get_if<T>` returns a pointer to the value if the specified type T
matches the current type of `std::variant`, nullptr otherwise.

```cpp
#include <channel_map.hpp>

void
your_function()
{
  auto& channel_map = chmap::ChannelMap::get_instance();
  channel_map.initialize("foo.csv");

  // std::get<T>
  {
    chmap::ChannelTuple detector(1, 2, 3, 4, 5);
    const auto& fe = channel_map.get("fe", detector);
    try {
      auto fe_id = std::get<chmap::number_t>(fe[0]);
      auto fe_ch = std::get<chmap::number_t>(fe[1]);
    } catch (const std::bad_variant_access& e) {
      std::cerr << "Bad variand access : " << e << std::endl;
    }
  }

  // std::get_if<T>
  {
    const auto& fe = channel_map.get("fe", {0, "a", 3, "x"});
    if (auto value_as_pointer = std::get_if<chmap::number_t>(&fe[0])) {
      std::cout << "The value is number : *value_as_pointer << std::endl;
    } else if (auto fe_id_as_pointer = std::get_if<std::string>(&fe[0])) {
      std::cout << "The value is string : *value_as_pointer << std::endl;
    } else {
      std::cerr << "The variant does not hold number or string" << std::endl;
    }
  }
    ...
  }
}
```

See also `skeleton.cpp` for implementation details.
