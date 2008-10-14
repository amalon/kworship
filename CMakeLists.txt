cmake_minimum_required(VERSION 2.6)

# custom modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

include_directories(include)

add_subdirectory (po)
add_subdirectory (mimetypes)
add_subdirectory (design)
add_subdirectory (kworship)
add_subdirectory (unipresent)

