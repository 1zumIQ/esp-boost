#
# Set variables
#
set(COMPONENT_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
file(GLOB_RECURSE COMPONENT_SRC_FILES ${COMPONENT_SRC_DIR}/*.cpp ${COMPONENT_SRC_DIR}/*.c)
set(COMPONENT_INCLUDE_DIRS ${COMPONENT_SRC_DIR})
set(COMPONENT_PUBLIC_REQUIRES pthread)

#
# Register component
#
idf_component_register(${COMPONENT_LIB}
    SRCS
        ${COMPONENT_SRC_FILES}
    INCLUDE_DIRS
        ${COMPONENT_INCLUDE_DIRS}
    REQUIRES
        ${COMPONENT_PUBLIC_REQUIRES}
)

#
# Set compiler options
#
target_compile_options(${COMPONENT_LIB}
    PUBLIC
        $<$<COMPILE_LANGUAGE:CXX>:-std=gnu++17>
)
