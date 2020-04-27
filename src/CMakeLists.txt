
add_executable(charls-js jslib.cpp)

target_link_libraries(charls-js PRIVATE charls)

#C++ 14
target_compile_features(charls-js PUBLIC cxx_std_14)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
	SET(linkFlags "-g4 -s NO_EXIT_RUNTIME=1")
else() # Either MinSizeRel, RelWithDebInfo or Release, all which run with optimizations enabled.
	SET(linkFlags "-O3 -s NO_EXIT_RUNTIME=1 -s DISABLE_EXCEPTION_CATCHING=1")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set_target_properties(
    charls-js 
    PROPERTIES 
    LINK_FLAGS "\
      --bind \
      -s DISABLE_EXCEPTION_CATCHING=1 \
      -s MALLOC=emmalloc \
      -s ALLOW_MEMORY_GROWTH=1 \
      -s TOTAL_MEMORY=1073741824 \
      -s ASSERTIONS=0 \
      -s FILESYSTEM=0 \
      -s EXPORTED_FUNCTIONS=[] \
      -s EXTRA_EXPORTED_RUNTIME_METHODS=[ccall] \
   ")
