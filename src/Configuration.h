//
// Created by Razvan Pascalau on 18/08/16.
//
#pragma once

#include <vector>
#include <unordered_map>
#include "SvgElement.h"

using ElementIndexType = uint32_t;
using ChildrenMapType = std::unordered_map<ElementIndexType, std::vector<ElementIndexType>>;

struct Configuration
{
	Configuration(std::vector<SvgElement> && elements_, std::unordered_map<std::string, std::vector<ElementIndexType>>&& groups_,
	              ChildrenMapType&& children_);

	std::vector<SvgElement> elements;
	std::unordered_map<std::string, std::vector<ElementIndexType>> groups;
	ChildrenMapType children;
};
