cmake_minimum_required (VERSION 3.1)
project(SVGRasterizer)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
#set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
#set(CMAKE_BUILD_FILES_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
#set(CMAKE_BUILD_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set (CMAKE_CXX_STANDARD 14)

##################### third party #####################
set(THIRD_PARTY_PATH "${CMAKE_SOURCE_DIR}/thirdparty")
set(ENUM_BITMASK_SRC	"${THIRD_PARTY_PATH}/EnumBitMask/EnumBitMask/EnumBitMask.cpp"
						"${THIRD_PARTY_PATH}/EnumBitMask/EnumBitMask/EnumBitMask.hpp")
set(CATCH_SRC "${THIRD_PARTY_PATH}/Catch/catch.hpp")
set(PUGIXML_SRC "${THIRD_PARTY_PATH}/pugixml/pugiconfig.hpp"
				"${THIRD_PARTY_PATH}/pugixml/pugixml.hpp"
				"${THIRD_PARTY_PATH}/pugixml/pugixml.cpp")
set(GSL_SRC "${THIRD_PARTY_PATH}/GSL/gsl/gsl"
			"${THIRD_PARTY_PATH}/GSL/gsl/gsl_assert"
			"${THIRD_PARTY_PATH}/GSL/gsl/gsl_byte"
			"${THIRD_PARTY_PATH}/GSL/gsl/gsl_util"
			"${THIRD_PARTY_PATH}/GSL/gsl/multi_span"
			"${THIRD_PARTY_PATH}/GSL/gsl/span"
			"${THIRD_PARTY_PATH}/GSL/gsl/string_span")
#set(RAPID_JSON_SRC "${THIRD_PARTY_PATH}/rapidjson/include)"

set(THIRD_PARTY_SRC ${ENUM_BITMASK_SRC}
					${CATCH_SRC}
					${PUGIXML_SRC}
					${GSL_SRC})

source_group("thirdparty\\EnumBitMask" FILES ${ENUM_BITMASK_SRC})
source_group("thirdparty\\Catch" FILES ${CATCH_SRC})
source_group("thirdparty\\pugixml" FILES ${PUGIXML_SRC})
source_group("thirdparty\\GSL" FILES ${GSL_SRC})
########################################################

set(SVG_RASTERIZER_PATH "${CMAKE_SOURCE_DIR}/src")
set(SVG_RASTERIZER_SRC	"${SVG_RASTERIZER_PATH}/main.cpp"
						"${SVG_RASTERIZER_PATH}/SvgParser.h"
						"${SVG_RASTERIZER_PATH}/SvgParser.cpp"
						"${SVG_RASTERIZER_PATH}/SvgElement.h"
						"${SVG_RASTERIZER_PATH}/SVGAttribute.hpp"
						"${SVG_RASTERIZER_PATH}/ConfigLoader.cpp"
						"${SVG_RASTERIZER_PATH}/ConfigLoader.h"
						"${SVG_RASTERIZER_PATH}/Configuration.cpp"
						"${SVG_RASTERIZER_PATH}/Configuration.h")
include_directories(${THIRD_PARTY_PATH}
					${SVG_RASTERIZER_PATH}
					${CMAKE_SOURCE_DIR}
					${THIRD_PARTY_PATH}/GSL
					${THIRD_PARTY_PATH}/rapidjson/include)
add_subdirectory(${THIRD_PARTY_PATH}/rapidjson)

add_executable(SVGRasterizer 	${SVG_RASTERIZER_SRC}
								${THIRD_PARTY_SRC})
