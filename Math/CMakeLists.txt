set(TargetName Math)

include(GroupSet)

set_group(Math_SRC
    Header:*.h
    Source:*.cpp
)


include_directories(${Math_INCLUDE} ${Utils_INCLUDE})

add_library(
    ${TargetName}
    ${Math_SRC}
)

target_link_libraries(
    ${TargetName}
    ${Utils_LIBRARY}
)


set_target_properties(
    ${TargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)
