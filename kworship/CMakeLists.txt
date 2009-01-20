project(kworship)

find_package(Sword REQUIRED)
find_package(KDE4 REQUIRED)
include (KDE4Defaults)
set(QT_USE_QTSQL 1)
include(${QT_USE_FILE})
include_directories(${KDE4_INCLUDES}
                    ${QT_INCLUDES}
                    ../unipresent/common
                    media
                    display
                    css
                    songdb
                    bible
                    playlist
                    archive
)
add_subdirectory (media)
add_subdirectory (display)
add_subdirectory (css)
add_subdirectory (songdb)
add_subdirectory (bible)
add_subdirectory (playlist)
add_subdirectory (archive)

set(kworship_SRCS
    main.cpp
    KwApplication.cpp
    kworship.cpp
    kworshipview.cpp
    prefsDisplay.cpp
    prefsSongDB.cpp
    DesktopView.cpp
    KwDatabaseSetup.cpp
    KwDocument.cpp
    KwPlugin.cpp
    KwPluginManager.cpp
    KwBiblePlugin.cpp
)

kde4_add_ui_files(kworship_SRCS
                  kworshipview_base.ui
                  prefs_base.ui
                  prefsDisplay_base.ui
                  prefsSongDB_base.ui
                  prefsPresentations_base.ui
)

kde4_add_kcfg_files(kworship_SRCS settings.kcfgc )

kde4_add_executable(kworship ${kworship_SRCS})

target_link_libraries(kworship
                      ${KDE4_KDEUI_LIBS}
                      ${KDE4_KIO_LIBS}
                      ${KDE4_KHTML_LIBS}
                      ${QT_LIBRARIES}
                      ${PHONON_LIBS}
                      ${SWORD_LIBS}
                      unipresent
                      kworshiparchive
                      kworshipplaylist
                      kworshipcss
                      kworshipbible
                      kworshipsongdb
                      kworshipdisplay
                      kworshipmedia
)

install(TARGETS kworship DESTINATION ${BIN_INSTALL_DIR} )


########### install files ###############

install( FILES kworship.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES kworship.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES kworshipui.rc  DESTINATION  ${DATA_INSTALL_DIR}/kworship )

