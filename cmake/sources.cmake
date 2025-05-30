# List directories containing header files
include_directories(
    app/src
    app/src/examples  # Add this if you have headers in examples folder
)

# Gather all source files
file(GLOB_RECURSE SOURCES 
    "app/src/*.cpp"
    "app/src/*.c"      # Add if you have C files
)

# Gather all header files (optional but good practice)
file(GLOB_RECURSE HEADERS
    "app/src/*.h"
    "app/src/*.hpp"
)

# If you want to see what files were found (for debugging)
message(STATUS "Found source files: ${SOURCES}")
message(STATUS "Found header files: ${HEADERS}")