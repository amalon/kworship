project(unipresent)

find_package(Qt4 REQUIRED)
include_directories(${QT_INCLUDES})

set(unipresent_SRCS
    UpManager.cpp
    UpBackend.cpp
    UpPresentation.cpp
    UpSlide.cpp
    UpSlidePreviewWidget.cpp
    UpSlideEditWidget.cpp
)

QT4_AUTOMOC(${unipresent_SRCS})

add_library(unipresent ${unipresent_SRCS})

