cmake_minimum_required(VERSION 3.24.1)
project (EDA_Tarea_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(code main.cpp) #include/utils.cpp include/sort.cpp include/time.cpp)
target_include_directories(code PUBLIC ${PROJECT_SOURCE_DIR}/include)