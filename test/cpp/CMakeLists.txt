
# Tests need to be added as executables first
add_executable(cpptest main.cpp)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(cpptest PRIVATE charls)

#C++ 14
target_compile_features(cpptest PUBLIC cxx_std_14)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
	SET(linkFlags "-g4 -s NO_EXIT_RUNTIME=1")
else() # Either MinSizeRel, RelWithDebInfo or Release, all which run with optimizations enabled.
	SET(linkFlags "-O3 -s NO_EXIT_RUNTIME=1 -s DISABLE_EXCEPTION_CATCHING=1")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")