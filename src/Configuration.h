//
// Created by Razvan Pascalau on 18/08/16.
//
#pragma once

#include <vector>
#include <string>
#include <sparsehash/dense_hash_map>
#include "SvgElement.h"

struct Configuration
{
	using ElementContainerType = std::vector<SvgElement>;
	using ChildrenMapType = google::dense_hash_map<std::string, std::vector<std::string>>;
	using ElementGroupType =  google::dense_hash_map<std::string, std::vector<std::string>>;

	Configuration(ElementContainerType&& elements_, ElementGroupType&& groups_,
	              ChildrenMapType&& children_);


	const ElementContainerType elements;
	const ElementGroupType groups;
	const ChildrenMapType children;
};
