cmake_minimum_required(VERSION 3.10)

project(DomoticSystem VERSION 1.0 LANGUAGES CXX)                  


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MAKE_PROGRAM "MinGW Makefiles")


set(SOURCES
    src/main.cpp
    src/DataStructure.cpp
    src/Interface.cpp
)

set(HEADERS
    include/DataStructure.h
    include/Interface.h
    include/Device.h
    include/EntryStructure.h
    include/ListaDevice.h
    include/time.h
)

add_executable(DomoticSystem ${SOURCES} ${HEADERS})

target_include_directories(DomoticSystem PRIVATE include)

set_target_properties(DomoticSystem PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_compile_options(DomoticSystem PRIVATE -O2)
