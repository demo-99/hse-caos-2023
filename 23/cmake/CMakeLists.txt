add_subdirectory(utils)
add_executable(my_executable main.c)
target_link_libraries(my_executable utils)
