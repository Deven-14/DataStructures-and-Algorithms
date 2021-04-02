project(singlyLinkedListTest)

find_package(GTest REQUIRED)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

add_executable(tests singlyLLTestMain.cpp ArrayTest.cpp)

add_test(NAME singlyLLTest COMMAND tests)

target_include_directories(tests PUBLIC ${GTEST_INCLUDE_DIRS})

target_link_libraries(tests singlyLL ${GTEST_LIBRARIES} pthread)
