add_library(civetweb STATIC civetweb/src/civetweb.c civetweb/include/civetweb.h)

target_include_directories(civetweb PUBLIC civetweb/include)

if(UNIX)
    target_link_libraries(civetweb PUBLIC pthread dl)
endif()