//
// Created by Razvan Pascalau on 16/08/16.
//

#include "ConfigLoader.h"
#include <cstdio>
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"

namespace ConfigLoader
{
	using rapidjson::Document;
	using rapidjson::Value;
	using rapidjson::SizeType;
	using rapidjson::FileReadStream;

	std::vector<SvgElement> getAllElements(rapidjson::Value::MemberIterator elementsIt)
	{
		std::vector<SvgElement> allElements;
		assert(elementsIt->value.IsArray());
		const Value& rawElements = elementsIt->value.GetArray();
		for (SizeType i = 0; i < rawElements.Size(); ++i)
		{
			const Value& singleElement = rawElements[i];
			assert(singleElement.IsString());
			allElements.emplace_back(SvgElement{singleElement.GetString()});
		}
		return allElements;
	}
	//TODO: create loadDocument function to pick up the load json functionality and return a rapidjson::Document
	Configuration loadConfigAtPath(const std::string& configPath)
	{
		//load json
		FILE* fp = fopen(configPath.c_str(), "r"); // non-Windows use "r"
		char readBuffer[65536];
		FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		Document doc;
		doc.ParseStream(is);
		fclose(fp);
		//end json loading

		assert(doc.IsObject());
		Value::MemberIterator elementsIt = doc.FindMember("elements");
		assert(elementsIt != doc.MemberEnd());
		std::vector<SvgElement> allTheElements = getAllElements(elementsIt);

		return Configuration();
	}

};