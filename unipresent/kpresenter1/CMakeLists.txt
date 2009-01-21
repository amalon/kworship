project(unipresent_kpresenter1)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include_directories(${KDE4_INCLUDES}
                    ${QT_INCLUDES}
)

set(unipresent_kpresenter1_SRCS
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

kde4_add_plugin(unipresent_kpresenter1 ${unipresent_kpresenter1_SRCS})

target_link_libraries(unipresent_kpresenter1
                      unipresent
                      ${KDE4_KDECORE_LIBS}
                      ${QT_LIBRARIES}
                      )

install( TARGETS unipresent_kpresenter1 DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES unipresent_kpresenter1.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )
