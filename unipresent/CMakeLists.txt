project(unipresent)

find_package(Qt4 REQUIRED)
include_directories(${QT_INCLUDES}
                    ../include
)

set(unipresent_SRCS
    UpManager.cpp
    UpPresentation.cpp
    UpSlide.cpp
    UpSlidePreviewWidget.cpp
    UpSlideEditWidget.cpp
)

add_library(unipresent ${unipresent_SRCS})

