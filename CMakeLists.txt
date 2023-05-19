cmake_minimum_required(VERSION 3.10)

# Set up the project and specify the required C++ version
project(SignEProject C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add SignE library
add_subdirectory(SignE)

# Add SignEditor console app
add_subdirectory(SignEditor)
