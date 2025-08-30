cmake_minimum_required(VERSION 3.20)

project(cpm_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Main executable ----
add_executable(cpm_example
    src/main.cpp
)
