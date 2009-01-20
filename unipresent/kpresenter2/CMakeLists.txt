project(unipresent_kpresenter2)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include_directories(${KDE4_INCLUDES}
                    ${QT_INCLUDES}
)

set(unipresent_kpresenter2_SRCS
    UpKpr2Backend.cpp
    UpKpr2Process.cpp
    UpKpr2Presentation.cpp
    UpKpr2Slide.cpp
)

kde4_add_plugin(unipresent_kpresenter2 ${unipresent_kpresenter2_SRCS})

target_link_libraries(unipresent_kpresenter2
                      unipresent
                      ${KDE4_KDECORE_LIBS}
                      ${KDE4_KIO_LIBS}
                      ${QT_LIBRARIES}
                      )

install(TARGETS unipresent_kpresenter2 DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES unipresent_kpresenter2.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )
