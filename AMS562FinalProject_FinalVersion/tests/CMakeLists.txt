# Enable testing
enable_testing()

# Find Google Test
find_package(GTest REQUIRED)

# Create the test executable
add_executable(AllTests
    test_main.cpp
    test_Address.cpp
    test_DeliveryRequest.cpp
    test_Route.cpp
    test_ScheduleBalanced.cpp
)

# Explicitly link the Google Test libraries
target_link_libraries(AllTests
    DeliveryLib
    /usr/local/lib/libgtest.a
    /usr/local/lib/libgtest_main.a
)

# Include directories for Google Test and source files
target_include_directories(AllTests PRIVATE
    /usr/local/include
    ${CMAKE_SOURCE_DIR}/src
)

# Register the tests with CTest
add_test(NAME AllTests COMMAND AllTests)
