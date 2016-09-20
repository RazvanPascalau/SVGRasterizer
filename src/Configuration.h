//
// Created by Razvan Pascalau on 18/08/16.
//
#pragma once

#include <vector>
#include <string>
#include <sparsehash/dense_hash_map>
#include <gsl/string_span>
#include "SvgElement.h"

namespace Configuration
{
	struct Raw
	{
		using ElementContainerType = std::vector<SvgElement>;
		using ChildrenMapType = google::dense_hash_map<std::string, std::vector<std::string>>;
		using ElementGroupType =  google::dense_hash_map<std::string, std::vector<std::string>>;
		Raw(Raw&&) = default;

		Raw(ElementContainerType&& elements_, ElementGroupType&& groups_,
		    ChildrenMapType&& children_);

		const ElementContainerType elements;
		const ElementGroupType groups;
		const ChildrenMapType children;
	};

	class Indexed
	{
		using ElementIndexType = uint32_t;
	public:
		Indexed() = default;
		Indexed(Raw&&)
		Indexed(const Indexed&) = default;
		Indexed(Indexed&&) = default;
		Indexed& operator =(const Indexed&) = default;
		Indexed& operator =(Indexed&&) = default;
		~Indexed() = default;



		ElementIndexType get_index_of_element(const std::string& name) const;

	private:
		const Raw raw_config;
	};
}
using Config = Configuration::Raw;
