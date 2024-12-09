# Create a library from the source files
add_library(DeliveryLib
    Address.hpp
    DeliveryRequest.hpp
    Route.hpp
    ScheduleBalanced.hpp
    main_balanced.cpp
)

# Create executables
add_executable(randomized_data_exporter randomized_data_exporter.cpp)
target_link_libraries(randomized_data_exporter DeliveryLib)

add_executable(delivery_balanced_scheduler main_balanced.cpp)
target_link_libraries(delivery_balanced_scheduler DeliveryLib)

add_executable(randomized_data_large_exporter randomized_data_large_exporter.cpp)
target_link_libraries(randomized_data_large_exporter DeliveryLib)

