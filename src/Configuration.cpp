//
// Created by Razvan Pascalau on 18/08/16.
//

#include "Configuration.h"

Configuration::Configuration(std::vector<SvgElement>&& elements_, std::unordered_map<std::string, std::vector<ElementIndexType>>&& groups_, ChildrenMapType&& children_)
	:elements(elements_)
	,groups(groups_)
	,children(children_)
{
	std::sort(std::begin(elements), std::end(elements));
}
