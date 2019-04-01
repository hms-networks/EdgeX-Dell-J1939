cmake_minimum_required(VERSION 3.0)

# Package support
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/src/c/cmake)


find_package (Libcsdk REQUIRED)
if (NOT LIBCSDK_FOUND)
  message (WARNING "csdk library or header not found")
endif ()

include_directories(
  ../../external/libsocketcan/include
  ../../external/LibJ1939/inc
)

# Set additional C compiler flags
if (DEFINED CMAKE_C_COMPILER_ID)
  if (CMAKE_C_COMPILER_ID MATCHES GNU)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wstrict-prototypes -Wmissing-prototypes")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb -O0")
    set (CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -ggdb -O0")
    set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")
    set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -O3")
   endif ()
endif ()

file (GLOB C_FILES *.c)
find_library(EDGEX_CSDK_RELEASE_LIB NAMES csdk)
find_library(J1939_STACK NAMES libXatJ1939.so PATHS ${CMAKE_SOURCE_DIR}/external/LibJ1939 NO_DEFAULT_PATH)
add_executable(device-j1939 ${C_FILES})
target_include_directories (device-j1939 PRIVATE .)
target_link_libraries (device-j1939 PUBLIC m PRIVATE ${EDGEX_CSDK_RELEASE_LIB})
target_link_libraries (device-j1939 PUBLIC m PRIVATE ${J1939_STACK})
