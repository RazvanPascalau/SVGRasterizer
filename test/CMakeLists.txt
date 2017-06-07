#Catch
add_library(Catch INTERFACE)
SET(CATCH_INCLUDE_DIR "${LIBS_PATH}/catch/single_include")
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})

enable_testing(true)
SET(SVG_RASTERIZER_TEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
SET(TEST_SVGRASTERIZER_SRC "${SVG_RASTERIZER_TEST_PATH}/Test_Bi_dir_unordered_map.cpp"
        "${SVG_RASTERIZER_TEST_PATH}/Test_Svg_parser.cpp")

add_executable(Test_SVGRasterizer ${TEST_SVGRASTERIZER_SRC})
target_link_libraries(Test_SVGRasterizer Catch
        SVGRasterizer)
