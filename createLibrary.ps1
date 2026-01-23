param([string]$ModuleName)

# 创建目录
New-Item -ItemType Directory -Path "$ModuleName/src"
New-Item -ItemType Directory -Path "$ModuleName/include"

# 生成 CMakeLists.txt
$cmakeContent = @"
cmake_minimum_required(VERSION 3.14)
project($ModuleName)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "src/*.cpp")

# 如果是库：
add_library($ModuleName STATIC \${SOURCES})
target_include_directories($ModuleName PUBLIC include)

# 如果是可执行文件，用下面这行代替上面两行：
add_executable($ModuleName \${SOURCES})
target_include_directories($ModuleName PRIVATE include)
"@

Set-Content -Path "$ModuleName/CMakeLists.txt" -Value $cmakeContent

Write-Host "Module '$ModuleName' created! Remember to add 'add_subdirectory($ModuleName)' in root CMakeLists.txt"