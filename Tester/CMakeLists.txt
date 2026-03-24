project(Tester)
set(CMAKE_BUILD_TYPE Debug)
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)

add_executable(Tester ${srcs})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(Tester
    PUBLIC
        Linear
        Util
)
