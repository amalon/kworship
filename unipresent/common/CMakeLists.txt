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
    UpSlideNode.cpp
    UpSlidePreviewWidget.cpp
    UpSlideEditWidget.cpp
)

kde4_add_library(unipresent SHARED ${unipresent_SRCS})

target_link_libraries(unipresent
                      ${KDE4_KDEUI_LIBS}
                      ${QT_LIBRARIES}
                      )

install( TARGETS unipresent DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( FILES unipresent_backend.desktop  DESTINATION  ${SERVICETYPES_INSTALL_DIR} )
