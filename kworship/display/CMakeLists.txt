project(kworshipdisplay)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworshipdisplay_MOC_SRCS
    KwLocalDisplay.cpp
    KwLocalDisplayPreview.cpp
)
set(kworshipdisplay_SRCS
    KwAbstractDisplay.cpp
    KwLocalDisplayController.cpp
    KwRemoteDisplayController.cpp
    KwRemoteDisplay.cpp
    KwLoggingDisplay.cpp
    KwDisplayMixer.cpp
    KwAbstractLayer.cpp
    KwImageLayer.cpp
    KwVideoLayer.cpp
    KwImageWidget.cpp
    KwTextLayer.cpp
    KwDisplayManager.cpp
    KwAbstractDisplayManager.cpp
    KwBackgroundManager.cpp
    KwTextManager.cpp
    KwOverlayManager.cpp
    ${kworshipdisplay_MOC_SRCS}
)

kde4_add_ui_files(kworshipdisplay_MOC_SRCS)

kde4_add_library(kworshipdisplay ${kworshipdisplay_SRCS})

