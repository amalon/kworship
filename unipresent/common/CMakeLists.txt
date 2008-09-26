project(unipresent)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include_directories(${KDE4_INCLUDES}
                    ${QT_INCLUDES}
)

set(unipresent_SRCS
    UpPresentationsModel.cpp
    UpManager.cpp
    UpManagerNode.cpp
    UpBackend.cpp
    UpBackendNode.cpp
    UpPresentation.cpp
    UpPresentationNode.cpp
    UpSlide.cpp
    UpSlidePreviewWidget.cpp
    UpSlideEditWidget.cpp
)

kde4_add_library(unipresent ${unipresent_SRCS})

