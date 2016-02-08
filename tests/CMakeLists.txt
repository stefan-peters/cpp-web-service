file(GLOB tests "*.cpp")

set(CMAKE_CTEST_COMMAND ctest --output-on-failure)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

foreach (test ${tests})
    get_filename_component(name ${test} NAME_WE)
    add_executable(${name} ${test})

    target_link_libraries(${name} PRIVATE CppWebService ${GTEST_BOTH_LIBRARIES})
    target_include_directories(${name} PRIVATE ${GTEST_INCLUDE_DIRS})

    add_test(NAME ${name} COMMAND ${name})
    add_dependencies(check ${name})
endforeach ()

