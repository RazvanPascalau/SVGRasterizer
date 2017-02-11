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
set(GSL_SRC "${THIRD_PARTY_PATH}/GSL/include/gsl/gsl"
			"${THIRD_PARTY_PATH}/GSL/include/gsl/gsl_assert"
			"${THIRD_PARTY_PATH}/GSL/include/gsl/gsl_byte"
			"${THIRD_PARTY_PATH}/GSL/include/gsl/gsl_util"
			"${THIRD_PARTY_PATH}/GSL/include/gsl/multi_span"
			"${THIRD_PARTY_PATH}/GSL/include/gsl/span"
			"${THIRD_PARTY_PATH}/GSL/include/gsl/string_span")
SET(SPARSE_HASH_SRC "${THIRD_PARTY_PATH}/sparsehash/dense_hash_map"
		"${THIRD_PARTY_PATH}/sparsehash/template_util.h"
		"${THIRD_PARTY_PATH}/sparsehash/type_traits.h")
#@TODO: refactor to include all third parties as EXTERNAL_PROJECT
SET(SPDLOG_SRC "${THIRD_PARTY_PATH}/spdlog/include/spdlog/async_logger.h"
        "${THIRD_PARTY_PATH}/spdlog/include/spdlog/logger.h"
        "${THIRD_PARTY_PATH}/spdlog/include/spdlog/spdlog.h")

set(THIRD_PARTY_SRC ${ENUM_BITMASK_SRC}
					${CATCH_SRC}
					${PUGIXML_SRC}
					${GSL_SRC}
                    ${SPDLOG_SRC})

source_group("thirdparty\\EnumBitMask" FILES ${ENUM_BITMASK_SRC})
source_group("thirdparty\\Catch" FILES ${CATCH_SRC})
source_group("thirdparty\\pugixml" FILES ${PUGIXML_SRC})
source_group("thirdparty\\GSL" FILES ${GSL_SRC})
source_group("thirdparty\\sparsehash" FILES ${SPARSE_HASH_SRC})
source_group("thirdparty\\spdlog" FILES {"SPDLOG_SRC"})
########################################################

set(SVG_RASTERIZER_PATH "${CMAKE_SOURCE_DIR}/src")
set(SVG_RASTERIZER_SRC	"${SVG_RASTERIZER_PATH}/main.cpp"
						"${SVG_RASTERIZER_PATH}/Svg_parser.hpp"
						"${SVG_RASTERIZER_PATH}/Svg_parser.cpp"
						"${SVG_RASTERIZER_PATH}/Svg_element.hpp"
						"${SVG_RASTERIZER_PATH}/Svg_attribute.hpp"
						"${SVG_RASTERIZER_PATH}/Config_reader.cpp"
						"${SVG_RASTERIZER_PATH}/Config_reader.hpp"
						"${SVG_RASTERIZER_PATH}/Configuration.cpp"
						"${SVG_RASTERIZER_PATH}/Configuration.hpp"
						"${SVG_RASTERIZER_PATH}/Config_writer.cpp"
						"${SVG_RASTERIZER_PATH}/Config_writer.hpp"
						"${SVG_RASTERIZER_PATH}/Utils.hpp"
		        		"${SVG_RASTERIZER_PATH}/Svg_element_processor.cpp"
						"${SVG_RASTERIZER_PATH}/Svg_element_processor.hpp")
include_directories(${THIRD_PARTY_PATH}
					${SVG_RASTERIZER_PATH}
					${CMAKE_SOURCE_DIR}
					${THIRD_PARTY_PATH}/GSL
					${THIRD_PARTY_PATH}/rapidjson/include
					${THIRD_PARTY_PATH}/sparsehash
                    ${THIRD_PARTY_PATH}/spdlog/include)
add_subdirectory(${THIRD_PARTY_PATH}/rapidjson)

add_executable(SVGRasterizer 	${SVG_RASTERIZER_SRC}
								${THIRD_PARTY_SRC})
