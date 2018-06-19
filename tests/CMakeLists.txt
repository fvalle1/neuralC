project(net_test)
add_subdirectory(googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}/)
include_directories(
        ${CMAKE_SOURCE_DIR}/.
)

add_executable(net_test
        ${CMAKE_SOURCE_DIR}/NeuralNet.cxx
        ${CMAKE_SOURCE_DIR}/Layer.cxx
        ${CMAKE_SOURCE_DIR}/Perceptron.cxx
        netTest.cxx)

target_link_libraries(net_test gtest gtest_main)