//
// Created by Razvan Pascalau on 16/08/16.
//

#include "ConfigLoader.h"
#include <iostream>
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"

namespace ConfigLoader
{
	using rapidjson::Document;
	using rapidjson::Value;
	using rapidjson::SizeType;
	using rapidjson::FileReadStream;
	using ChildrenMapType = std::unordered_map<ElementIndexType, std::vector<ElementIndexType>>;

	////// TODO: move this from here /////////////////////////////////////////////////////////
	std::ostream& operator<<(std::ostream& stream, const SvgElement& element_to_print)
	{
		stream << element_to_print.name;
		return stream;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vector_to_print)
	{
		for (const auto& element : vector_to_print)
		{
			stream << element << ", ";
		}
		stream << std::endl;
		return stream;
	}
	//////////////////////////////////////////////////////////////////////////////////////////

	std::vector<SvgElement> getAllElements(const Document& doc)
	{
		// load elements
		const auto elements_it = doc.FindMember("elements");
		assert(elements_it != doc.MemberEnd());
		assert(elements_it->value.IsArray());

		std::vector<SvgElement> all_elements;
		const auto raw_elements = elements_it->value.GetArray();;
		for (SizeType i = 0; i < raw_elements.Size(); ++i)
		{
			const Value& singleElement = raw_elements[i];
			assert(singleElement.IsString());
			all_elements.emplace_back(SvgElement{singleElement.GetString()});
		}
		std::sort(std::begin(all_elements), std::end(all_elements));
		return all_elements;
	}

	ElementIndexType getIndexOfElementName(const std::string& name, const std::vector<SvgElement>& all_elements_)
	{
		ElementIndexType index_for_name{std::numeric_limits<ElementIndexType>::max()};
		assert(std::is_sorted(std::begin(all_elements_), std::end(all_elements_)));
		auto searched_name_it = std::lower_bound(std::begin(all_elements_), std::end(all_elements_),
		                                         name);

		if (searched_name_it == all_elements_.end() || searched_name_it->name != name)
		{
			//TODO: Throw exception
		}
		index_for_name = std::distance(all_elements_.begin(), searched_name_it);
		return index_for_name;
	}


	std::unordered_map<std::string, std::vector<ElementIndexType>>
	getAllElementGroups(const Document& doc, const std::vector<SvgElement>& all_elements_)
	{
		const auto element_groups_it = doc.FindMember("element_groups");
		assert(element_groups_it != doc.MemberEnd());
		assert(element_groups_it->value.IsArray());
		const auto raw_array_of_groups = element_groups_it->value.GetArray();
		std::unordered_map<std::string, std::vector<ElementIndexType>> all_element_groups;
		for (const auto& raw_single_group: raw_array_of_groups)
		{
			assert(raw_single_group.IsObject());
			const auto& single_group = raw_single_group.GetObject();
			//group name
			const auto group_name_it = single_group.FindMember("name");
			assert(group_name_it != single_group.MemberEnd());
			assert(group_name_it->value.IsString());
			const auto group_name = std::string {group_name_it->value.GetString(), group_name_it->value.GetStringLength()};

			//all the elements that are part of the group
			std::vector<ElementIndexType> single_group_members;
			const auto raw_single_group_members = single_group.FindMember("elements");
			assert(raw_single_group_members != single_group.MemberEnd());
			assert(raw_single_group_members->value.IsArray());
			const auto raw_array_of_group_members = raw_single_group_members->value.GetArray();

			for (const auto& raw_single_group_element : raw_array_of_group_members)
			{
				ElementIndexType index_for_name{std::numeric_limits<ElementIndexType>::max()};
				assert(raw_single_group_element.IsString());
				const auto group_element_as_string = std::string{raw_single_group_element.GetString(),
				                                                 raw_single_group_element.GetStringLength()};
				index_for_name = getIndexOfElementName(group_element_as_string, all_elements_);
				all_element_groups[group_name].emplace_back(index_for_name);
			}
		}

		for (auto& array_name_pair : all_element_groups)
		{
			auto& element_vector = array_name_pair.second;
			std::sort(std::begin(element_vector), std::end(element_vector));
		}
		// TODO: this line is for debug purposes, should be removed
		std::cout << all_elements_;
		return all_element_groups;
	}

	ChildrenMapType getAllElementChildren(const Document& doc, const std::vector<SvgElement>& all_elements_)
	{
		ChildrenMapType all_element_children;
		all_element_children.reserve(all_elements_.size()); //TODO: check if this is helping with anything

		// load elements
		const auto element_children_it = doc.FindMember("element_children");
		assert(element_children_it != doc.MemberEnd());
		assert(element_children_it->value.IsArray());
		const auto raw_element_children_array = element_children_it->value.GetArray();

		for (const auto& raw_element_children_obj : raw_element_children_array)
		{
			assert(raw_element_children_obj.IsObject());

			//parent
			const auto raw_parent_element = raw_element_children_obj.FindMember("parent");
			assert(raw_parent_element != raw_element_children_obj.MemberEnd());
			assert(raw_parent_element->value.IsString());
			const auto& parent_element_name = raw_parent_element->value.GetString();
			ElementIndexType parent_element_index = getIndexOfElementName(parent_element_name, all_elements_);

			//children
			std::vector<ElementIndexType> all_children;
			const auto raw_children_array_it = raw_element_children_obj.FindMember("children");
			assert(raw_children_array_it != raw_element_children_obj.MemberEnd());
			assert(raw_children_array_it->value.IsArray());
			const auto raw_children_array = (raw_children_array_it->value.GetArray());
			for (const auto& raw_child : raw_children_array)
			{
				assert(raw_child.IsString());
				const auto child = std::string{raw_child.GetString(), raw_child.GetStringLength()};
				all_children.emplace_back(getIndexOfElementName(child, all_elements_));
			}
		}
		return all_element_children;
	}

	Document loadDocument(const std::string& documentPath)
	{
		FILE *fp = fopen(documentPath.c_str(), "r"); // non-Windows use "r"
		char readBuffer[65536]; //TODO: check this magic constant
		FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		Document doc;
		doc.ParseStream(is);
		fclose(fp);

		return
			doc;
	}

	Configuration loadConfigAtPath(const std::string& config_path)
	{
		Document doc = loadDocument(config_path);
		assert(doc.IsObject());

		auto all_elements = getAllElements(doc);
		auto all_element_groups = getAllElementGroups(doc, all_elements);
		auto all_element_children = getAllElementChildren(doc, all_elements);

		return Configuration(std::move(all_elements), std::move(all_element_groups));
	}

};