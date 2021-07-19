cmake_minimum_required(VERSION 3.9) 

project(Parser-Verilog LANGUAGES CXX) 
include(CTest) 

# Turn on the verbose
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

# add the binary tree to the search path for include files
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(parser-verilog)


# -----------------------------------------------------------------------------
# Flex & Bison
# -----------------------------------------------------------------------------

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(verilog_parser
             ${PROJECT_SOURCE_DIR}/parser-verilog/verilog_parser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/verilog_parser.tab.cc)
FLEX_TARGET(verilog_lexer
            ${PROJECT_SOURCE_DIR}/parser-verilog/verilog_lexer.l
            ${CMAKE_CURRENT_BINARY_DIR}/verilog_lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(verilog_lexer verilog_parser)


# -----------------------------------------------------------------------------
# Example program 
# -----------------------------------------------------------------------------

# Set the output folder to example
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/example)

# A sample parser
add_executable(sample_parser
  ${PROJECT_SOURCE_DIR}/example/sample_parser.cpp
  ${FLEX_verilog_lexer_OUTPUTS}
  ${BISON_verilog_parser_OUTPUTS}
)

# A drop-in replacement OpenTimer Verilog parser
add_executable(ot_parser
  ${PROJECT_SOURCE_DIR}/example/ot_parser.cpp
  ${FLEX_verilog_lexer_OUTPUTS}
  ${BISON_verilog_parser_OUTPUTS}
)



# -----------------------------------------------------------------------------
# Unittest
# -----------------------------------------------------------------------------

enable_testing()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/unittest)

# Regression  
set(VP_UTEST_DIR ${PROJECT_SOURCE_DIR}/unittest) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${VP_UTEST_DIR})

add_executable(regression unittest/regression.cpp ${FLEX_verilog_lexer_OUTPUTS} ${BISON_verilog_parser_OUTPUTS})
add_test(regression ${VP_UTEST_DIR}/regression)

