include_directories(..)

add_executable(dfs dfs.cpp)
add_executable(dfs_test dfs_test.cpp)
target_link_libraries(dfs_test PRIVATE Catch2::Catch2WithMain)

add_executable(dfs_path dfs_path.cpp)
