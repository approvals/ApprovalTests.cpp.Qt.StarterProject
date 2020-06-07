set(TEST_NAME StarterProjectQt.tests)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES
        main.cpp
        WidgetsTest.cpp
        Tutorial.cpp)
add_executable(${TEST_NAME} ${SOURCE_FILES})
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

find_package(Qt5 COMPONENTS Widgets Test REQUIRED)
target_link_libraries(${TEST_NAME} ApprovalTestsQt::ApprovalTestsQt Catch2::Catch2 Qt5::Widgets Qt5::Test)
