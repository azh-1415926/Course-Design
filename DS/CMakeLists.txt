file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.c include/*.h)
add_library(DS STATIC ${srcs})
target_include_directories(DS PUBLIC include)