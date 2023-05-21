set(TargetName Math)

include(GroupSet)

set_group(Math_SRC
    Header:*.h
    Source:*.cpp
    Header/Bin:Bin/*.h
    Source/Bin:Bin/*.cpp
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.h.in 
               ${CMAKE_CURRENT_BINARY_DIR}/Config.h)

include_directories(
 ${Math_INCLUDE} 
 ${Utils_INCLUDE}
 ${CMAKE_CURRENT_BINARY_DIR}/../
)

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
