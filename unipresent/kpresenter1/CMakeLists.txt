project(unipresentkpresenter1)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include_directories(${KDE4_INCLUDES}
                    ${QT_INCLUDES}
)

set(unipresentkpresenter1_SRCS
    UpKpr1Dcop.cpp
    UpKpr1AppsDcop.cpp
    UpKpr1KpresenterDcop.cpp
    UpKpr1Backend.cpp
    UpKpr1Presentation.cpp
    UpKpr1PresentationDcop.cpp
    UpKpr1ViewDcop.cpp
    UpKpr1Slide.cpp
    UpKpr1SlideDcop.cpp
)

kde4_add_library(unipresentkpresenter1 STATIC ${unipresentkpresenter1_SRCS})

