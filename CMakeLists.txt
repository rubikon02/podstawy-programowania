#cmake_minimum_required(VERSION 3.23)
cmake_minimum_required(VERSION 3.16)
project(Programy C)

set(CMAKE_C_STANDARD 11)
#link_libraries(ws2_32 wsock32)




set (EXCLUDE_DIR "cmake-build-debug")
file(GLOB_RECURSE FILES RELATIVE ${CMAKE_SOURCE_DIR} *.c)
foreach(file ${FILES})
    string (FIND ${file} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
    if (${EXCLUDE_DIR_FOUND} EQUAL -1)
        get_filename_component(fname ${file} NAME)
        get_filename_component(fpath ${file} PATH)
        message(STATUS "Adding target for ${fname} in ${fpath}")
        add_executable(${fpath}_${fname} ${fpath}/${fname})
    endif()
endforeach()
