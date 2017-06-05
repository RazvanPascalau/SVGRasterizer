#set(THIRD_PARTY_PATH "${CMAKE_SOURCE_DIR}/thirdparty")
#set(SVG_RASTERIZER_SRC_PATH "${CMAKE_SOURCE_DIR}/src")

#Catch
add_library(Catch INTERFACE)

#unit tests
target_include_directories(Catch INTERFACE ${LIBS_PATH}/Catch)
include_directories(${SVG_RASTERIZER_SRC_PATH})
enable_testing()

SET(SVG_RASTERIZER_TEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
SET(TEST_SVGRASTERIZER_SRC "${SVG_RASTERIZER_TEST_PATH}/Test_Bi_dir_unordered_map.cpp"
        "${SVG_RASTERIZER_TEST_PATH}/Test_Svg_parser.cpp")

add_executable(Test_SVGRasterizer ${TEST_SVGRASTERIZER_SRC})
target_link_libraries(Test_SVGRasterizer Catch
        SVGRasterizer)
