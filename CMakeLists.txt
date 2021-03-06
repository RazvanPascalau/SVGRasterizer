cmake_minimum_required(VERSION 3.8)
project(SVGRasterizer)

set(CMAKE_CXX_STANDARD 17) # long live cmake 3.8
##################### third party #####################

set(LIBS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs")
set(INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LIBRARY_NAME "SVGRasterizer")

#pugixml
add_subdirectory("${LIBS_PATH}/pugixml" "libs/pugixml")
include_directories(libs/pugixml/src)

#GSL
add_subdirectory("${LIBS_PATH}/GSL" "libs/GSL")

#spdlog
add_subdirectory("${LIBS_PATH}/spdlog" "libs/spdlog")

#rapidjson
add_library(RapidJSON INTERFACE)
target_include_directories(RapidJSON INTERFACE libs/rapidjson)
include_directories(libs/rapidjson/include)
########################################################

set(SVG_RASTERIZER_SRC_PATH "${CMAKE_SOURCE_DIR}/src")
set(SVG_RASTERIZER_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/include")
set(SVG_RASTERIZER_INCLUDE "${SVG_RASTERIZER_INCLUDE_PATH}/SVGRasterizer/Svg_parser.hpp"
        "${SVG_RASTERIZER_INCLUDE_PATH}/SVGRasterizer/Svg_attribute.hpp"
        "${SVG_RASTERIZER_INCLUDE_PATH}/SVGRasterizer/Config_reader.hpp"
        "${SVG_RASTERIZER_INCLUDE_PATH}/SVGRasterizer/Configuration.hpp"
        "${SVG_RASTERIZER_INCLUDE_PATH}/SVGRasterizer/Config_writer.hpp"
        "${SVG_RASTERIZER_INCLUDE_PATH}/SVGRasterizer/Svg_element_processor.hpp"
        "${SVG_RASTERIZER_INCLUDE_PATH}/SVGRasterizer/Utils.hpp"
        "${SVG_RASTERIZER_INCLUDE_PATH}/SVGRasterizer/Svg_element.hpp"
        "${SVG_RASTERIZER_INCLUDE_PATH}/SVGRasterizer/Bi_dir_unordered_map.hpp")

set(SVG_RASTERIZER_SRC
        "${SVG_RASTERIZER_SRC_PATH}/Svg_parser.cpp"
        "${SVG_RASTERIZER_SRC_PATH}/Config_reader.cpp"
        "${SVG_RASTERIZER_SRC_PATH}/Configuration.cpp"
        "${SVG_RASTERIZER_SRC_PATH}/Config_writer.cpp"
        "${SVG_RASTERIZER_SRC_PATH}/Svg_element_processor.cpp"
        "${SVG_RASTERIZER_SRC_PATH}/Svg_element.cpp")

add_library(${LIBRARY_NAME} ${SVG_RASTERIZER_INCLUDE}
        ${SVG_RASTERIZER_SRC})

target_link_libraries(${LIBRARY_NAME} GSL
        RapidJSON
        pugixml
        spdlog)

target_include_directories(${LIBRARY_NAME} PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
        $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>
        )

target_include_directories(${LIBRARY_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )
#unit tests and test target
add_subdirectory(test)


