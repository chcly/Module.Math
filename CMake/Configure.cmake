include(GitUpdate)
if (NOT GitUpdate_SUCCESS)
    return()
endif()

include(StaticRuntime)
include(GTestUtils)
include(ExternalTarget)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(Math_BUILD_TEST          "Build the unit test program." ON)
option(Math_AUTO_RUN_TEST       "Automatically run the test program." ON)
option(Math_USE_STATIC_RUNTIME  "Build with the MultiThreaded(Debug) runtime library." ON)
include(${Math_SOURCE_DIR}/CMake/Globals.cmake)

if (Math_USE_STATIC_RUNTIME)
    set_static_runtime()
else()
    set_dynamic_runtime()
endif()


DefineExternalTargetEx(
    Utils Extern
    ${Math_SOURCE_DIR}/Internal/Utils 
    ${Math_SOURCE_DIR}/Internal/Utils
    ${Math_BUILD_TEST}
    ${Math_AUTO_RUN_TEST}
)

configure_gtest(${Math_SOURCE_DIR}/Test/googletest 
                ${Math_SOURCE_DIR}/Test/googletest/googletest/include)


set(Configure_SUCCEEDED TRUE)