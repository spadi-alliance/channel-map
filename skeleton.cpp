#include <cstdlib>
#include <iostream>

#include <channel-map.hpp>
#include <index-tuple.hpp>
#include <stopwatch.hpp>

enum EArgs {
  kProcess, kInputCSV, kNArgs
};

int main(int argc, char* argv[]) {
  if (argc < kNArgs) {
    std::cout << "Usage: " << argv[kProcess] << " [InputCSV]" << std::endl;
    return EXIT_SUCCESS;
  }

  std::string input_csv(argv[kInputCSV]);

  auto& channel_map = cmap::ChannelMap::GetInstance();
  channel_map.InitializeFromCSV(input_csv);
  channel_map.DebugPrint();

  /*
    usage example
  */
  if (input_csv == "test.csv") {
    {
      cmap::IndexTuple det(170, 30, 0, 262, 0);
      const auto& fe = channel_map.Det2Fe(det);
      std::cout << "det = " << det << std::endl
                << "-> fe = " << fe << std::endl;

      for (const auto& e : fe) {
        std::cout << "element : " << e << std::endl;
      }


      /*
        std::get<T> returns the value if the specified type T
        matches the current type of std::variant,
        otherwise it throws a std::bad_variant_access exception.
      */
      std::cout << std::string(80, '=') << std::endl
                << "fe[0] : " << std::get<cmap::number_t>(fe.at(0))
                << " fe[1] : " << std::get<cmap::number_t>(fe.at(1))
                << " fe[2] : " << std::get<std::string>(fe.at(2))
                << std::endl;

      try {
        auto value = std::get<std::string>(fe.at(0));
        std::cout << "fe[0] : " << value << std::endl;
      } catch (const std::bad_variant_access& e) {
        std::cerr << "Bad variant access : " << e.what() << std::endl;
      }

      /*
        std::get_if<T> returns a pointer to the value if the specified
        type T matches the current type of std::variant, nullptr otherwise.
      */
      std::cout << std::string(80, '=') << std::endl
                << "fe[0] : " << *std::get_if<cmap::number_t>(&fe.at(0))
                << " fe[1] : " << *std::get_if<cmap::number_t>(&fe.at(1))
                << " fe[2] : " << *std::get_if<std::string>(&fe.at(2))
                << std::endl;

      if (auto value = std::get_if<cmap::number_t>(&fe.at(2))) {
        std::cout << "The value is number : " << *value << std::endl;
      } else if (auto value = std::get_if<std::string>(&fe.at(2))) {
        std::cout << "The value is string : " << *value << std::endl;
      } else {
        std::cerr << "The variant does not hold number or string" << std::endl;
      }
    }

    /*
      If the key is missing, a null tuple is returned.
     */
    {
      cmap::IndexTuple det(0, 1, 2, 3);
      const auto& fe = channel_map.Det2Fe(det);
      std::cout << "fe = " << fe << std::endl;
    }
  }

  return EXIT_SUCCESS;
}
