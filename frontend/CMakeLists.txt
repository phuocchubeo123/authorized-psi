
file(GLOB_RECURSE SRCS *.cpp)

add_executable(frontend main.cpp perf.cpp)

target_link_libraries(frontend volePSI_Tests)


if(VOLE_PSI_NO_LTO)
    target_link_options(frontend PUBLIC "-fno-lto")
endif()

add_executable(data_gen data_gen.cpp)
target_link_libraries(data_gen volePSI_Tests)



if(MSVC)
    target_compile_options(frontend PRIVATE $<$<COMPILE_LANGUAGE:CXX>:/std:c++${VOLE_PSI_STD_VER}>)
    #target_compile_options(libOTe PRIVATE -openmp:experimental)
else()
    target_compile_options(frontend PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-std=c++${VOLE_PSI_STD_VER}>)
endif()