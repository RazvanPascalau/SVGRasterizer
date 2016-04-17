cmake_minimum_required (VERSION 2.8)
project(SVGRasterizer)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

##################### third party #####################
set(THIRD_PARTY_PATH "${CMAKE_SOURCE_DIR}/thirdparty")
set(ENUM_BITMASK_SRC	"${THIRD_PARTY_PATH}/EnumBitMask/EnumBitMask/EnumBitMask.cpp"
						"${THIRD_PARTY_PATH}/EnumBitMask/EnumBitMask/EnumBitMask.hpp")
set(CATCH_SRC "${THIRD_PARTY_PATH}/Catch/catch.hpp")
set(PUGIXML_SRC "${THIRD_PARTY_PATH}/pugixml/src/pugiconfig.hpp"
				"${THIRD_PARTY_PATH}/pugixml/src/pugixml.hpp"
				"${THIRD_PARTY_PATH}/pugixml/src/pugixml.cpp")
SET(THIRD_PARTY_SRC ${ENUM_BITMASK_SRC}
					${CATCH_SRC}
					${PUGIXML_SRC})
########################################################

add_executable(SVGRasterizer ${THIRD_PARTY_SRC})