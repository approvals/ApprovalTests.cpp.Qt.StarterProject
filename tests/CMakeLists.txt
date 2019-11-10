cmake_minimum_required(VERSION 3.8)
project(StarterProjectQt.tests)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES
        main.cpp
        DemoTest.cpp
        NewTest.cpp
        WidgetsTest.cpp
        Tutorial.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} )
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

find_package(Qt5 COMPONENTS Widgets Test REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Test)
