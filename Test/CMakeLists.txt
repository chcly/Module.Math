set(TestTargetName ${TargetName}Test)
include(TestDirectory)
gen_path_to_here()

set(TestTarget_SRC
    Test1.cpp
)

include_directories(
    ${GTEST_INCLUDE}
    ${Math_INCLUDE}
    ${Utils_INCLUDE}
)

add_executable(
    ${TestTargetName}
    ${TestTarget_SRC}
)
target_link_libraries(
    ${TestTargetName} 
    ${GTEST_LIBRARY}
    ${Math_LIBRARY}
    ${Utils_LIBRARY}
)

set_target_properties(
    ${TestTargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)


if (Math_AUTO_RUN_TEST)
    run_test(${TestTargetName})
endif()
