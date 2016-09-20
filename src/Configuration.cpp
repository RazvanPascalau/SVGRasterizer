//
// Created by Razvan Pascalau on 18/08/16.
//

#include "Configuration.h"

namespace Configuration
{
	Raw::Raw(Raw::ElementContainerType&& elements_, Raw::ElementGroupType&& groups_,
	         Raw::ChildrenMapType&& children_)
		: elements(elements_), groups(groups_), children(children_)
	{
	}

	Indexed::ElementIndexType Indexed::get_index_of_element(const std::string& name)
	{
		Indexed::ElementIndexType index_of_name = std::numeric_limits<Indexed::ElementIndexType>::max();
		const auto& all_elements = raw_config.elements;
		uint32_t index_for_name{std::numeric_limits<uint32_t>::max()};
		assert(std::is_sorted(std::begin(all_elements), std::end(all_elements)));
		auto searched_name_it = std::lower_bound(std::begin(all_elements), std::end(all_elements),
		                                         name);

		if (searched_name_it != all_elements.end() && searched_name_it->name == name)
		{
			index_of_name = std::distance(all_elements.begin(), searched_name_it);
		}
		return index_of_name;
	}

}
