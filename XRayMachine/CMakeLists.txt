project(XRayMachine)

##root
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS RIO Net)
include(${ROOT_USE_FILE})


ROOT_GENERATE_DICTIONARY(G__XRayMachine XRayMachine.h LINKDEF)
add_library(XRayMachine SHARED XRayMachine.cxx G__XRayMachine.cxx)
target_link_libraries(XRayMachine ${ROOT_LIBRARIES})

include_directories(
        ${CMAKE_SOURCE_DIR}/.
)

add_executable(xray
        XRayMachine.cxx
        ${CMAKE_SOURCE_DIR}/Perceptron.cxx
        ${CMAKE_SOURCE_DIR}/Layer.cxx
        ${CMAKE_SOURCE_DIR}/NeuralNet.cxx
        ${CMAKE_SOURCE_DIR}/run_xray.cxx
        ${CMAKE_SOURCE_DIR}/Mainroot.cxx
        )

target_link_libraries(xray XRayMachine)