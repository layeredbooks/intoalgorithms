include_directories(..)

add_executable(bfs bfs.cpp)
add_executable(bfs_test bfs_test.cpp)
target_link_libraries(bfs_test PRIVATE Catch2::Catch2WithMain)

add_executable(bfs_path bfs_path.cpp)
add_executable(bfs_path_test bfs_path_test.cpp)
target_link_libraries(bfs_path_test PRIVATE Catch2::Catch2WithMain)
