cmake_minimum_required(VERSION 3.15.5)

SET(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

project(ESMTOOLKIT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../install)

set(CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE x64)

find_package(LibXml2 REQUIRED)

set(SOURCES xmlUtils.cpp include/xmlUtils.h pch.cpp include/pch.h esmReader.cpp)

add_executable(esmToolkit ${SOURCES})
target_include_directories(esmToolkit PUBLIC include)

target_link_libraries(esmToolkit PRIVATE LibXml2::LibXml2)

add_subdirectory(subrecords)
add_subdirectory(records)

#install(TARGETS esmToolkit DESTINATION .)
#install(IMPORTED_RUNTIME_ARTIFACTS LibXml2::LibXml2)
