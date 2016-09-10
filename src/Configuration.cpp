//
// Created by Razvan Pascalau on 18/08/16.
//

#include "Configuration.h"

Configuration::Configuration(Configuration::ElementContainerType&& elements_, Configuration::ElementGroupType&& groups_,
                             Configuration::ChildrenMapType&& children_)
	: elements(elements_), groups(groups_), children(children_)
{

}
