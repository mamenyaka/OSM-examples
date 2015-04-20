/*
 * buszjarat.cpp
 * This is a simple program that prints the bus stop names and coordinates from the input file.
 */

#include <osmium/memory/buffer.hpp>
#include <osmium/io/any_input.hpp>
#include <osmium/index/map/sparse_mem_table.hpp>
#include <osmium/osm.hpp>

#include <iostream>

typedef osmium::index::map::SparseMemTable<osmium::unsigned_object_id_type, size_t> offset_index_type;

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " OSMFILE\n";
    exit(1);
  }

  osmium::memory::Buffer buffer = osmium::io::read_file(argv[1]);

  offset_index_type node_index;
  size_t m_offset = 0;

  for (const auto& item : buffer)
  {
    if (item.type() == osmium::item_type::node)
    {
      const osmium::Node& node = static_cast<const osmium::Node&>(item);

      node_index.set(node.positive_id(), m_offset);
      m_offset += node.byte_size();
    }
    else if (item.type() == osmium::item_type::relation)
    {
      const osmium::Relation& relation = static_cast<const osmium::Relation&>(item);

      const char* route = relation.get_value_by_key("route", "");
      if (!strncmp(route, "bus", 3))
      {
        const char *ref = relation.get_value_by_key("ref", "");
        const char *from = relation.get_value_by_key("from", "");
        const char *to = relation.get_value_by_key("to", "");

        std::cout << ref << " (" << from << " -> " << to << ") - " << relation.user() << std::endl;

        for (const auto& member : relation.members())
        {
          if (member.type() == osmium::item_type::node && !strncmp(member.role(), "stop", 4))
          {
            try
            {
              const size_t offset = node_index.get(member.positive_ref());
              const osmium::Node &node = buffer.get<const osmium::Node>(offset);

              std::cout << node.get_value_by_key("name", "none") << " " << node.location() << " - " << node.user() << std::endl;
            }
            catch (std::runtime_error& e)
            {
              std::cout << e.what() << std::endl;
            }
          }
        }

        std::cout << std::endl;
      }
    }
  }

  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
