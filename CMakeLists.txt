cmake_minimum_required(VERSION 3.7)
project(s_fractal_cpp VERSION 1.0)

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})

set(EXECUTABLE_OUTPUT_PATH "../bin")

add_executable(s_fractal s_fractal_main.cpp s_fractal_scenario.cpp s_fractal.cpp s_image_data.cpp s_xml_doc.cpp s_xml_element.cpp)
target_link_libraries(s_fractal ${LIBXML2_LIBRARIES})