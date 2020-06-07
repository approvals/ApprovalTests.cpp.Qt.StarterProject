if(NOT TARGET ApprovalTestsQt)
    set(LIB_NAME ApprovalTestsQt)
    add_library(${LIB_NAME} INTERFACE)
    target_include_directories(${LIB_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
    add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})
endif()

if(NOT TARGET Catch2)
    set(CMAKE_CXX_STANDARD 11)
    add_library(Catch2 INTERFACE)
    target_include_directories(Catch2
            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

    # Mimic the library names in Catch2's own CMake files:
    add_library(Catch2::Catch2 ALIAS Catch2)

    # This one is historical, left over from when ApprovalTests.cpp was first created.
    # We could encourage users to move away from it.
    add_library(catch2 ALIAS Catch2)
endif()
