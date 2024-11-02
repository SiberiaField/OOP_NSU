cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(Time_Building)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_TEST "Building with or without tests, default without tests" OFF)

add_executable(main main.cpp Time.cpp)

if(ENABLE_TEST)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    # Добавляем тестовое приложение
    add_executable(timeTests tests.cpp Time.cpp)

    # Связываем тестовое приложение с библиотекой и GoogleTest
    target_link_libraries(timeTests PRIVATE GTest::gtest_main)

    # Находим тесты
    include(GoogleTest)
    gtest_discover_tests(timeTests)
    enable_testing()
endif()