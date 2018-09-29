
file(GLOB_RECURSE CXX_SRC_FILES_FOR_TOOLS *.cpp *.h)

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    add_custom_target(
        format
        COMMAND ${CLANG_FORMAT}
        -i
        -style=WebKit
        ${CXX_SRC_FILES_FOR_TOOLS}
        )
endif()

find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    add_custom_target(
        tidy
        COMMAND /usr/bin/clang-tidy
        ${CXX_SRC_FILES_FOR_TOOLS}
        -config=''
        --
        -std=c++17
        )
endif()
