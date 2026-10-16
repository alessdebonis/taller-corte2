cmake_minimum_required(VERSION 3.10)
project(TallerCorte2 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Genera build/compile_commands.json para que VS Code encuentre Eigen
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------
# Eigen
# 1. Si Eigen esta instalado en el sistema, se usa ese.
# 2. Si no, se usa la copia incluida en third_party/eigen.
# ------------------------------------------------------------
find_package(Eigen3 QUIET NO_MODULE)

if(TARGET Eigen3::Eigen)
    message(STATUS "Eigen: usando la version instalada en el sistema (${Eigen3_VERSION})")
else()
    message(STATUS "Eigen: usando la copia incluida en third_party/eigen")
    add_library(Eigen3::Eigen INTERFACE IMPORTED)
    set_target_properties(Eigen3::Eigen PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen")
endif()

# Laboratorio 2.1: tensores y operaciones basicas
add_executable(lab2_1 lab2_1/main.cpp)
target_link_libraries(lab2_1 Eigen3::Eigen)

# Laboratorio 2.2: regresion lineal y regresion logistica
add_executable(lab2_2 lab2_2/main.cpp)
target_link_libraries(lab2_2 Eigen3::Eigen)
