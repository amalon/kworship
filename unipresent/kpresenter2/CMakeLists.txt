project(unipresentkpresenter2)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include_directories(${KDE4_INCLUDES}
                    ${QT_INCLUDES}
)

set(unipresentkpresenter2_SRCS
    UpKpr2Backend.cpp
    UpKpr2Process.cpp
    UpKpr2Presentation.cpp
    UpKpr2Slide.cpp
)

kde4_add_library(unipresentkpresenter2 STATIC ${unipresentkpresenter2_SRCS})

