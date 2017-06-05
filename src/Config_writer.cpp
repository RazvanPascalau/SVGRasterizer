//
// Created by Razvan Pascalau on 04/12/2016.
//
#include <rapidjson/prettywriter.h>
#include "Config_writer.hpp"
#include "rapidjson/filewritestream.h"
#include "rapidjson/document.h"
#include <fstream>

namespace configuration {
    namespace writer {
        using rapidjson::Writer;
        using rapidjson::StringBuffer;
        using rapidjson::PrettyWriter;

        template<typename Writer>
        auto display(Writer& writer)
        {
            writer.StartObject();  // write "{"
            writer.String("hello"); // write string "hello"
            writer.String("world");
            writer.String("t");
            writer.Bool(true);   // write boolean value true
            writer.String("f");
            writer.Bool(false);
            writer.String("n");
            writer.Null();        // write null
            writer.String("i");
            writer.Uint(123);     // write unsigned integer value
            writer.String("pi");
            writer.Double(3.1416); // write floating point numbers
            writer.String("a");
            writer.StartArray();  // write "["
            for (unsigned i = 0; i<4; i++)
                writer.Uint(i);
            writer.EndArray();   // End Array "]"
            writer.EndObject();  // end Object "}"
        }

        template<typename Writer>
        auto write_elements(const Raw_config& raw_config, Writer& writer)
        {
            writer.Key("elements");
            writer.StartArray();
            for (const auto& single_element : raw_config.elements) {
                writer.String(single_element.get_name().c_str());
            }
            writer.EndArray();
        }

        template<typename Writer>
        auto write_element_groups(const Raw_config& raw_config, Writer& writer)
        {
            writer.Key("element_groups");
            writer.StartArray();
            for (const auto& single_group : raw_config.groups) {
                writer.StartObject();
                writer.Key("name");
                writer.String(single_group.first.c_str()); //group name

                writer.Key("elemeants");
                writer.StartArray();
                for (const auto& single_group_element : single_group.second) {
                    writer.String(single_group_element.c_str());
                }
                writer.EndArray();
                writer.EndObject();
            }
            writer.EndArray();
        }

        template<typename Writer>
        auto write_attributes(const Raw_config& raw_config, Writer& writer)
        {
            writer.Key("attributes");
            writer.StartArray();
            //TODO: implement this
            writer.EndArray();
        }

        template<typename Writer>
        auto write_element_children(const Raw_config& raw_config, Writer& writer)
        {
            //TODO: think about a possible strategy to replace elements that form a group with the group itself to preserve 0% input/output diff
            writer.Key("element_children");
            writer.StartArray();
            for (const auto& single_group : raw_config.children) {
                writer.StartObject();
                writer.Key("parent");
                writer.String(single_group.first.c_str()); //parent name

                writer.Key("children");
                writer.StartArray();
                for (const auto& single_child : single_group.second) {
                    writer.String(single_child.c_str());
                }
                writer.EndArray();
                writer.EndObject();
            }
            writer.EndArray();
        }

        auto write_to_file(const Indexed_config& config, const std::string& out_file_path) -> void
        {
            write_to_file(config.get_raw_config(), out_file_path);
        }

        auto write_to_file(const Raw_config& raw_config, const std::string& out_file_path) -> void
        {
            StringBuffer s;
            PrettyWriter<StringBuffer> writer(s);
//            display(writer);
            writer.StartObject();
            write_elements(raw_config, writer);
            write_element_groups(raw_config, writer);
            write_attributes(raw_config, writer);
            write_element_children(raw_config, writer);
            writer.EndObject();
//            std::cout << s.GetString() << std::endl;   // GetString() stringify the
            std::ofstream out_file_stream(out_file_path, std::ios_base::out);
            out_file_stream << s.GetString();
//            for(const auto& single_element : raw_config.elements)
//            {
//                writer.String(single_element.name);
//            }

        }
    }
}
