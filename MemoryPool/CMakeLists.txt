# CMakeList.txt: LDST 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
project(MemoryPool)
# 将源代码添加到此项目的可执行文件。
file(GLOB SOURCES 
    "src/*.cpp"
)

add_library(MemoryPool STATIC ${SOURCES})

target_include_directories(MemoryPool PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

# TODO: 如有需要，请添加测试并安装目标。
