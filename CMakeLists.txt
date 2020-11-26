cmake_minimum_required(VERSION 3.15)
project(Pacman)

set(CMAKE_CXX_STANDARD 14)

if(APPLE)
    # MacOS settings
    link_directories(/usr/local/opt/libomp/lib)
    include_directories(/usr/local/opt/libomp/include)

    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)

    if(CMAKE_C_COMPILER_ID MATCHES "Clang\$")
        set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp")
        set(OpenMP_C_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY omp)
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang\$")
        set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")
        set(OpenMP_CXX_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY omp)
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework GLUT -framework OpenGL -Wno-deprecated")

elseif(UNIX)
    # Linux settings
    set(OpenMP_C_FLAGS "-fopenmp")
    set(OpenMP_C_LIB_NAMES "omp")
    set(OpenMP_omp_LIBRARY omp)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lGL -lglut -lGLU")
endif()

find_package(OpenMP REQUIRED)

add_subdirectory(src)
target_link_libraries(Pacman PRIVATE OpenMP::OpenMP_CXX)
