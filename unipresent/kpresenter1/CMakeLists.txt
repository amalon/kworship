project(unipresentkpresenter1)

find_package(Qt4 REQUIRED)
include_directories(${QT_INCLUDES})

set(unipresentkpresenter1_SRCS
    UpKpr1Dcop.cpp
    UpKpr1AppsDcop.cpp
    UpKpr1KpresenterDcop.cpp
    UpKpr1Backend.cpp
    UpKpr1Presentation.cpp
    UpKpr1PresentationDcop.cpp
#    UpKpr1Slide.cpp
#    UpKpr1SlideDcop.cpp
)

QT4_AUTOMOC(${unipresentkpresenter1_SRCS})

add_library(unipresentkpresenter1 STATIC ${unipresentkpresenter1_SRCS})

