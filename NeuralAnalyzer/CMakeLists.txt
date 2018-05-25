project(NeuralAnalyzer)

##root
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS RIO Net)
include(${ROOT_USE_FILE})


ROOT_GENERATE_DICTIONARY(G__NeuralAnalyzer NeuralAnalyzer.h LINKDEF)
add_library(NeuralAnalyzer SHARED NeuralAnalyzer.cxx G__NeuralAnalyzer.cxx)
target_link_libraries(NeuralAnalyzer ${ROOT_LIBRARIES})

include_directories(
        ${CMAKE_SOURCE_DIR}/.
)


add_executable(plotter
        NeuralAnalyzer.cxx
        ${CMAKE_SOURCE_DIR}/run_dataset.cxx
        ${CMAKE_SOURCE_DIR}/run_plot.cxx
        ${CMAKE_SOURCE_DIR}/Mainroot.cxx
        )

target_link_libraries(plotter NeuralAnalyzer)
