file(GLOB sources *.cpp)
file(GLOB headers include/CppWebService/*.h)

add_library(CppWebService STATIC ${sources} ${headers})

target_link_libraries(CppWebService PRIVATE civetweb)
target_include_directories(CppWebService PUBLIC ../include PRIVATE ../include/CppWebService)