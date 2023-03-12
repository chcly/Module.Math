cmake_minimum_required(VERSION 3.15)
project(Math)

# Use C++-17 by default.
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the module path to include scripts
# CMake - Contains project local modules.
#
# CMake/Modules - Contains project independent modules.
#   GitUpdate.cmake invokes python ${Math_SOURCE_DIR}/gitupdate.py
#   to pull all submodules and update to head.
#   If this fails, it will attempt to invoke git directly to pull 
#   submodules. 
list(APPEND CMAKE_MODULE_PATH 
  ${Math_SOURCE_DIR}/CMake 
  ${Math_SOURCE_DIR}/CMake/Modules
)
include(Configure)
if (NOT Configure_SUCCEEDED)
   return()
endif()



if (Math_ExternalTarget)
    set(TargetFolders ${Math_TargetFolders})
    set(TargetName    ${Math_TargetName})
    set(TargetGroup   ${Math_TargetGroup})
else()
    add_subdirectory(CMake)
    add_subdirectory(Internal/Utils)

    set(TargetFolders TRUE)
    set(TargetName Math)
    set(TargetGroup )

    set(Math_INCLUDE  ${Math_SOURCE_DIR})
    set(Math_LIBRARY  ${TargetName})
endif()

add_subdirectory(Math)

if (Math_BUILD_TEST)
    if (NOT Math_ExternalTarget)
        add_gtest_source(Extern/ThirdParty)
    endif()

    set(TargetGroup Units)
    add_subdirectory(Test)
endif()
