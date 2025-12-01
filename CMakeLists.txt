cmake_minimum_required(VERSION 3.8)
project(minishell)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file (GLOB_RECURSE sources
		"${CMAKE_SOURCE_DIR}/srcs/*c"
)

add_executable(minishell ${sources})
target_link_libraries(minishell PUBLIC "${CMAKE_SOURCE_DIR}/libft_42/libft.a")

target_include_directories(minishell PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(minishell PUBLIC "${CMAKE_SOURCE_DIR}/libft_42")


