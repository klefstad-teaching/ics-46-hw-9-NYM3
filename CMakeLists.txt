cmake_minimum_required(VERSION 3.20)

project(HW9 CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dijkstras source files
set(DIJKSTRAS_SRC_FILES
  src/dijkstras.h
  src/dijkstras.cpp
)

# Build dijkstra_main executable
add_executable(dijkstra_main
  ${DIJKSTRAS_SRC_FILES}
  src/dijkstras_main.cpp
)

# Ladder source files
set(LADDER_SRC_FILES
  src/ladder.h
  src/ladder.cpp
)

# Build ladder_main executable
add_executable(ladder_main
  ${LADDER_SRC_FILES}
  src/ladder_main.cpp
)

# Find GoogleTest package for testing
find_package(GTest)
if (GTest_FOUND)
  # List test source files
  set(STUDENT_TEST_FILES
    gtest/gtestmain.cpp
    gtest/student_gtests.cpp
  )

  # Build the student_gtests executable with both dijkstras and ladder sources
  add_executable(student_gtests 
    ${STUDENT_TEST_FILES}
    ${DIJKSTRAS_SRC_FILES}
    ${LADDER_SRC_FILES}
  )
  
  # Include directories for the tests
  target_include_directories(student_gtests PRIVATE src ${GTEST_INCLUDE_DIRS})
  
  # Link GoogleTest libraries
  target_link_libraries(student_gtests PRIVATE ${GTEST_LIBRARIES})
  
  # Add sanitizer flags (AddressSanitizer and UndefinedBehaviorSanitizer)
  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(student_gtests PRIVATE -fsanitize=address,undefined)
    target_link_options(student_gtests PRIVATE -fsanitize=address,undefined)
  endif()
endif()
