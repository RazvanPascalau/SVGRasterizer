cmake_minimum_required (VERSION 2.8)
project(SVGRasterizer)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_BUILD_FILES_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_BUILD_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

##################### third party #####################
set(THIRD_PARTY_PATH "${CMAKE_SOURCE_DIR}/thirdparty")
set(ENUM_BITMASK_SRC	"${THIRD_PARTY_PATH}/EnumBitMask/EnumBitMask/EnumBitMask.cpp"
						"${THIRD_PARTY_PATH}/EnumBitMask/EnumBitMask/EnumBitMask.hpp")
set(CATCH_SRC "${THIRD_PARTY_PATH}/Catch/catch.hpp")
set(PUGIXML_SRC "${THIRD_PARTY_PATH}/pugixml/pugiconfig.hpp"
				"${THIRD_PARTY_PATH}/pugixml/pugixml.hpp"
				"${THIRD_PARTY_PATH}/pugixml/pugixml.cpp")
SET(THIRD_PARTY_SRC ${ENUM_BITMASK_SRC}
					${CATCH_SRC}
					${PUGIXML_SRC})

source_group("thirdparty\\EnumBitMask" FILES ${ENUM_BITMASK_SRC})
source_group("thirdparty\\Catch" FILES ${CATCH_SRC})
source_group("thirdparty\\pugixml" FILES ${PUGIXML_SRC})
########################################################

set(SVG_RASTERIZER_PATH "${CMAKE_SOURCE_DIR}/src")
set(SVG_RASTERIZER_SRC	"${SVG_RASTERIZER_PATH}/main.cpp"
						"${SVG_RASTERIZER_PATH}/SVGParser.hpp"
						"${SVG_RASTERIZER_PATH}/SVGParser.cpp")
include_directories(${THIRD_PARTY_PATH}
					${SVG_RASTERIZER_PATH})

add_executable(SVGRasterizer 	${SVG_RASTERIZER_SRC}
								${THIRD_PARTY_SRC})
