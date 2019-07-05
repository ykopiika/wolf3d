cmake_minimum_required(VERSION 3.12.1)
project(wolf3d C)

find_library(libsdl SDL2)

set(CMAKE_C_STANDARD 99)

set(LIB_PATH			./)
set(SRC_PATH			./)
set(INC_PATH			./)
set(LFT_PATH			libft)
set(LFT_NAME			ft)
set(LFT_LIB				${LFT_PATH})

aux_source_directory(	${LFT_LIB} LFT_SRC)
aux_source_directory(	${SRC_PATH} PROJECT_SOURCE_FILES)
add_library(			${LFT_NAME} STATIC ${LFT_SRC})

#include_directories(./)
add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCE_FILES})

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")
target_link_libraries(${PROJECT_NAME} ${LFT_NAME} ${libsdl})

#set(GCC_COVERAGE_COMPILE_FLAGS "-fsanitize=\"address\" -g -fno-omit-frame-pointer")
#-Weverything