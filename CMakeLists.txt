cmake_minimum_required(VERSION 3.26)
project(Programmig_SecondSem C)

set(CMAKE_C_STANDARD 11)

add_executable(Programmig_SecondSem main.c
)


add_subdirectory(libs)
target_link_libraries(Programmig_SecondSem algorithms)
target_link_libraries(Programmig_SecondSem data_struct)
add_executable(gg test.c)
add_executable(vector_test vector_test.c)
add_executable(matrix_test matrix_test.c)
add_executable(matrix_ex_tests matrix_ex_tests.c)
