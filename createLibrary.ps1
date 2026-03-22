param([string]$ModuleName,[string]$model)
$exists = Test-Path -Path $ModuleName
if($model -eq "force" -and $exists)
{
    Remove-Item -Path $ModuleName -Force -Recurse
}
# 创建目录
New-Item -ItemType Directory -Path "$ModuleName/src"
New-Item -ItemType Directory -Path "$ModuleName/include"

# 生成库文件的 CMakeLists.txt
$cmakeContent = @"
project($ModuleName)
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(`${PROJECT_NAME} STATIC `${srcs})

target_include_directories(`${PROJECT_NAME}
    PUBLIC
        `${PROJECT_SOURCE_DIR}/include
)
"@

Set-Content -Path "$ModuleName/CMakeLists.txt" -Value $cmakeContent

# 生成默认源文件
$mainSource = @"
#include <iostream>
int main()
{
    std::cout << "This is $ModuleName" << std::endl;
    return 0;
}
"@

Set-Content -Path "$ModuleName/src/$ModuleName.cpp" -Value $mainSource
#  创建默认头文件
$mainHeader = @"
#pragma once
namespace $ModuleName
{
}
"@
Set-Content -Path "$ModuleName/include/$ModuleName.h" -Value $mainHeader
$cmakeFile = Join-Path  $PWD.Path "CMakeLists.txt"
$content = Get-Content $cmakeFile
$targetLine="add_subdirectory($ModuleName)"
# 查找库是否已经存在
$position = -1
for ( $i = 0;  $i -lt  $content.Count;  $i++) {
    if ( $content[$i] -eq  $targetLine) {
        Write-Host "Library $ModuleName already exists in CMakeLists.txt"
        $position = $i
        break
    }
}
if ($position -eq -1 -and $content.Count -gt 0) {
$newContent = $content + @"
#添加 $ModuleName 到项目中
add_subdirectory($ModuleName)
"@
$utf8NoBom = New-Object System.Text.UTF8Encoding( $false)
[System.IO.File]::WriteAllLines( $cmakeFile,  $newContent,  $utf8NoBom)
Write-Host "Successfully inserted 'add_subdirectory( $ModuleName )' into CMakeLists.txt"
}

