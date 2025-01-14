# Versione minima di CMake
cmake_minimum_required(VERSION 3.10)

# Nome del progetto
project(MyProject)

# Specifica il C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Percorsi per i file sorgente e header
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Lista dei file sorgente
set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Interface.cpp
    ${SRC_DIR}/DataStructure.cpp
)

# Lista dei file header
set(HEADERS
    ${INCLUDE_DIR}/time.h
    ${INCLUDE_DIR}/Device.h
    ${INCLUDE_DIR}/Interface.h
    ${INCLUDE_DIR}/DataStructure.h
    ${INCLUDE_DIR}/EventLogger.h
    ${INCLUDE_DIR}/EntryStructure.h
    ${INCLUDE_DIR}/ListaDevice.h
)

# Include directory per i file header
include_directories(${INCLUDE_DIR})

# Aggiunge l'eseguibile
add_executable(MyExecutable ${SOURCES} ${HEADERS})

# Specifica la cartella di output per l'eseguibile
set_target_properties(MyExecutable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Aggiunge l'ottimizzazione -O2 per il compilatore
target_compile_options(MyExecutable PRIVATE -O2)
