project(unipresent_okular)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include_directories(${KDE4_INCLUDES}
                    ${QT_INCLUDES}
)

set(unipresent_okular_SRCS
    UpOkBackend.cpp
    UpOkProcess.cpp
    UpOkPresentation.cpp
    UpOkSlide.cpp
)

kde4_add_plugin(unipresent_okular ${unipresent_okular_SRCS})

target_link_libraries(unipresent_okular
                      unipresent
                      ${KDE4_KDECORE_LIBS}
                      ${KDE4_KIO_LIBS}
                      ${QT_LIBRARIES}
                      )

install( TARGETS unipresent_okular DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES unipresent_okular.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )
