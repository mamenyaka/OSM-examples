/*
 * utcak.cpp
 * This is a simple program that prints the streets from the input file.
 */

#include <osmium/memory/buffer.hpp>
#include <osmium/io/any_input.hpp>
#include <osmium/osm.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " OSMFILE\n";
    exit(1);
  }

  osmium::memory::Buffer buffer = osmium::io::read_file(argv[1]);

  for (const auto& item : buffer)
  {
    if (item.type() == osmium::item_type::way)
    {
      const osmium::Way& way = static_cast<const osmium::Way&>(item);

      const char* name = way.get_value_by_key("name");
      const char* highway = way.get_value_by_key("highway");

      if (name && highway)
        std::cout << "[" << way.user() << "] " << name << " "
                  << "(" << highway << ")" << std::endl;
    }
  }

  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
