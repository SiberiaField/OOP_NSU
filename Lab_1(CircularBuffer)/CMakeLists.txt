cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавляем библиотеку
add_library(CircularBuffer CircularBuffer.cpp)

# Добавляем тестовое приложение
add_executable(cbTest tests.cpp)

# Связываем тестовое приложение с библиотекой и GoogleTest
target_link_libraries(cbTest PRIVATE CircularBuffer GTest::gtest_main)

# Находим тесты
include(GoogleTest)
gtest_discover_tests(cbTest)
enable_testing()