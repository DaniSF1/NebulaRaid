cmake_minimum_required(VERSION 3.10)

set(SOURCES
    ../src/entities/Bullet.cpp
    ../src/core/GameObject.cpp
)

add_executable(PoolTests PoolTests.cpp ${SOURCES})

target_include_directories(PoolTests PRIVATE ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/tests)

add_test(NAME PoolTests COMMAND PoolTests)
