set(THIRD_PARTY_PATH "${CMAKE_SOURCE_DIR}/thirdparty")

#pugixml
add_subdirectory("${THIRD_PARTY_PATH}/pugixml" "thirdparty/pugixml")

#GSL
add_subdirectory("${THIRD_PARTY_PATH}/GSL" "thirdparty/GSL")
#spdlog
add_subdirectory("${THIRD_PARTY_PATH}/spdlog" "thirdparty/spdlog")

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

include_directories(${THIRD_PARTY_PATH}
        ${SVG_RASTERIZER_SRC_PATH}
        ${CMAKE_SOURCE_DIR}
        ${SVG_RASTERIZER_INCLUDE_PATH})
add_subdirectory("${THIRD_PARTY_PATH}/rapidjson" "thirdparty/rapidjson")

add_library(SVGRasterizer ${SVG_RASTERIZER_INCLUDE}
        ${SVG_RASTERIZER_SRC})
target_link_libraries(SVGRasterizer GSL
        pugixml
        spdlog)
