//
// Created by Razvan Pascalau on 16/08/16.
//

#include "Config_reader.hpp"
#include <iostream>
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"

namespace configuration {
    namespace reader {
        using rapidjson::Document;
        using rapidjson::Value;
        using rapidjson::SizeType;
        using rapidjson::FileReadStream;

        ////// TODO: move this from here /////////////////////////////////////////////////////////
        std::ostream& operator<<(std::ostream& stream, const Svg_element& element_to_print)
        {
            stream << gsl::to_string(element_to_print.get_name());
            return stream;
        }

        template<typename T>
        std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vector_to_print)
        {
            for (const auto& element : vector_to_print) {
                stream << element << ", ";
            }
            stream << std::endl;
            return stream;
        }
        //////////////////////////////////////////////////////////////////////////////////////////

        auto get_all_elements(const Document& doc) -> Raw_config::Element_container_type
        {
            // load elements
            const auto elements_it = doc.FindMember("elements");
            assert(elements_it!=doc.MemberEnd());
            assert(elements_it->value.IsArray());

            std::vector<Svg_element> all_elements;
            const auto raw_elements = elements_it->value.GetArray();
            for (const auto& singleElement : raw_elements) {
                assert(singleElement.IsString());
                all_elements.emplace_back(singleElement.GetString());
            }
            std::sort(std::begin(all_elements), std::end(all_elements));
            return all_elements;
        }

        auto get_all_element_groups(const Document& doc,
                const std::vector<Svg_element>& all_elements_) -> Raw_config::Element_group_type
        {
            const auto element_groups_it = doc.FindMember("element_groups");
            assert(element_groups_it!=doc.MemberEnd());
            assert(element_groups_it->value.IsArray());
            const auto raw_array_of_groups = element_groups_it->value.GetArray();

            Raw_config::Element_group_type all_element_groups;
            all_element_groups.set_empty_key(std::string{""});
            for (const auto& raw_single_group: raw_array_of_groups) {
                assert(raw_single_group.IsObject());
                const auto& single_group = raw_single_group.GetObject();
                //group name
                const auto group_name_it = single_group.FindMember("name");
                assert(group_name_it!=single_group.MemberEnd());
                assert(group_name_it->value.IsString());
                const auto group_name = std::string {group_name_it->value.GetString(),
                                                     group_name_it->value.GetStringLength()};

                //all the elements that are part of the group
                std::vector<std::string> single_group_members;
                const auto raw_single_group_members = single_group.FindMember("elements");
                assert(raw_single_group_members!=single_group.MemberEnd());
                assert(raw_single_group_members->value.IsArray());
                const auto raw_array_of_group_members = raw_single_group_members->value.GetArray();

                for (const auto& raw_single_group_element : raw_array_of_group_members) {
                    assert(raw_single_group_element.IsString());
                    single_group_members.emplace_back(raw_single_group_element.GetString(),
                            raw_single_group_element.GetStringLength());
                }
                all_element_groups[group_name] = std::move(single_group_members);
            }

            for (auto& array_name_pair : all_element_groups) {
                auto& element_vector = array_name_pair.second;
                std::sort(std::begin(element_vector), std::end(element_vector));
            }
            // TODO: this line is for debug purposes, should be removed
            std::cout << all_elements_;
            return all_element_groups;
        }

        auto
        getAllElementChildren(const rapidjson::Document& doc, const std::vector<Svg_element>& all_elements_,
                const Raw_config::Element_group_type& element_groups_) -> Raw_config::Children_map_type
        {
            Raw_config::Children_map_type all_element_children;
            all_element_children.set_empty_key(std::string{""});

            // load elements
            const auto element_children_it = doc.FindMember("element_children");
            assert(element_children_it!=doc.MemberEnd());
            assert(element_children_it->value.IsArray());
            const auto raw_element_children_array = element_children_it->value.GetArray();

            for (const auto& raw_element_children_obj : raw_element_children_array) {
                assert(raw_element_children_obj.IsObject());

                //parent
                const auto raw_parent_element = raw_element_children_obj.FindMember("parent");
                assert(raw_parent_element!=raw_element_children_obj.MemberEnd());
                assert(raw_parent_element->value.IsString());
                const auto& parent_element_name = raw_parent_element->value.GetString();

                //children
                std::vector<std::string> all_children;
                const auto raw_children_array_it = raw_element_children_obj.FindMember("children");
                assert(raw_children_array_it!=raw_element_children_obj.MemberEnd());
                assert(raw_children_array_it->value.IsArray());
                const auto raw_children_array = (raw_children_array_it->value.GetArray());
                for (const auto& raw_child : raw_children_array) {
                    assert(raw_child.IsString());
                    auto child = std::string{raw_child.GetString(), raw_child.GetStringLength()};
                    if (element_groups_.count(child)>0) // the name is a group name
                    {
                        const auto& group_with_current_name = const_cast<Raw_config::Element_group_type&>(element_groups_)[child];
                        all_children.insert(std::end(all_children), std::begin(group_with_current_name),
                                std::end(group_with_current_name));//we replace the group with it's elements
                    }
                    else // otherwise it's a simple element
                    {
                        all_children.emplace_back(std::move(child));
                    }
                    std::sort(std::begin(all_children), std::end(all_children));
                    all_element_children[parent_element_name] = std::move(all_children);
                }
            }
            return all_element_children;
        }

        auto loadDocument(const std::string& documentPath) -> Document
        {
            FILE* fp = fopen(documentPath.c_str(), "r"); // non-Windows use "r"
            char readBuffer[65536]; //TODO: check this magic number
            FileReadStream is(fp, readBuffer, sizeof(readBuffer));
            Document doc;
            doc.ParseStream(is);
            fclose(fp);

            return doc;
        }

        auto readRawConfigAtPath(const std::string& config_path) -> Raw_config
        {
            Document doc = loadDocument(config_path);
            assert(doc.IsObject());

            auto all_elements = get_all_elements(doc);
            auto all_element_groups = get_all_element_groups(doc, all_elements);
            auto all_element_children = getAllElementChildren(doc, all_elements, all_element_groups);
            const auto& configuration = Raw_config(std::move(all_elements), std::move(all_element_groups),
                    std::move(all_element_children));
            return configuration;
        }

        auto readIndexedConfigAtPath(const std::string& config_path) -> Indexed_config
        {
            auto raw_config = readRawConfigAtPath(config_path);
            Indexed_config indexed_config(std::move(raw_config));
            return indexed_config;
        }

    }
}