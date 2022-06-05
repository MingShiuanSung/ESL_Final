file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(platform-dac-four-core
ethernet.cpp
display.cpp
${HEADERS})

target_include_directories(platform-dac-four-core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(riscv-vp-dac-four-core
        main.cpp)

target_link_libraries(riscv-vp-dac-four-core rv32 platform-dac-four-core platform-common gdb-mc ${Boost_LIBRARIES} ${SystemC_LIBRARIES} pthread)

INSTALL(TARGETS riscv-vp RUNTIME DESTINATION bin)
