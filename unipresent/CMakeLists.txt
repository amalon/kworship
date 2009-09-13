find_package(Qt4 REQUIRED)
include_directories(${QT_INCLUDES}
                    common)

# Common unipresent code
add_subdirectory (common)

# KPresenter 1 backend
# (KPresenter 1 isn't available for windows)
if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  add_subdirectory (kpresenter1)
endif (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

# KPresenter 2 backend
add_subdirectory (kpresenter2)

# OpenOffice.org backend
add_subdirectory (openoffice.org)

# Okular backend
add_subdirectory (okular)
