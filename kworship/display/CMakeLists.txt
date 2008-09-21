project(kworshipdisplay)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworshipdisplay_SRCS
    KwAbstractDisplay.cpp
    KwLocalDisplayController.cpp
    KwRemoteDisplayController.cpp
    KwLocalDisplay.cpp
    KwLocalDisplayPreview.cpp
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
)

kde4_add_library(kworshipdisplay ${kworshipdisplay_SRCS})

