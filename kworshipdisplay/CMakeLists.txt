project(kworshipdisplay)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include_directories(${KDE4_INCLUDES}
                    ${QT_INCLUDES}
                    ../include
)

set(kworshipdisplay_MOC_SRCS
    KwLocalDisplay.cpp
    KwLocalDisplayPreview.cpp
)
set(kworshipdisplay_SRCS
    KwAbstractDisplay.cpp
    KwLocalDisplayController.cpp
    KwRemoteDisplayController.cpp
    KwRemoteDisplay.cpp
    KwDisplayMixer.cpp
    KwAbstractLayer.cpp
    KwImageLayer.cpp
    KwImageWidget.cpp
    KwTextLayer.cpp
    ${kworshipdisplay_MOC_SRCS}
)

kde4_add_ui_files(kworshipdisplay_MOC_SRCS)

kde4_add_library(kworshipdisplay ${kworshipdisplay_SRCS})

