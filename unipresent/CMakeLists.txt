find_package(Qt4 REQUIRED)
include_directories(${QT_INCLUDES}
                    common)

add_subdirectory (common)
add_subdirectory (kpresenter1)
add_subdirectory (openoffice.org)

