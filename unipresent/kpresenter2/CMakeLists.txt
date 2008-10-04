project(unipresentkpresenter2)

find_package(Qt4 REQUIRED)
include_directories(${QT_INCLUDES})

set(unipresentkpresenter2_SRCS
    UpKpr2Backend.cpp
    UpKpr2Presentation.cpp
    UpKpr2Slide.cpp
)

QT4_AUTOMOC(${unipresentkpresenter2_SRCS})

add_library(unipresentkpresenter2 STATIC ${unipresentkpresenter2_SRCS})

