set(TargetName Math)
include(GroupSet)

set_group(Math_SRC
    Header:*.h
    Source:*.cpp
    Header/Bin:Bin/*.h
    Source/Bin:Bin/*.cpp
)

# Keep in the source directory, so that include paths remain simplified.
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.h.in 
               ${CMAKE_CURRENT_SOURCE_DIR}/Config.h) 

include_directories(
 ${Math_INCLUDE} 
 ${Utils_INCLUDE}
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
