project(kworship)

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
                    playlist
                    archive
)
add_subdirectory (songdb)
add_subdirectory (bible)

set(kworshiparchive_SRCS
    archive/KwResourceLink.cpp
    archive/KwResourceManager.cpp
    archive/KwDataFile.cpp
    archive/KwArchive.cpp
)
set(kworshipcss_SRCS
    css/KwCssAbstractStyle.cpp
    css/KwCssAbstractStyleState.cpp
    css/KwCssScope.cpp
    css/KwCssScopeKey.cpp
    css/KwCssStyles.cpp
    css/KwCssStyle.cpp
    css/KwCssStyleStates.cpp
    css/KwCssStyleRule.cpp
    css/KwCssStyleSheet.cpp
    css/KwCssStyleSheetFile.cpp
)
set(kworshipdisplay_SRCS
    display/KwAbstractDisplay.cpp
    display/KwLocalDisplayController.cpp
    display/KwRemoteDisplayController.cpp
    display/KwLocalDisplay.cpp
    display/KwLocalDisplayPreview.cpp
    display/KwRemoteDisplay.cpp
    display/KwLoggingDisplay.cpp
    display/KwDisplayMixer.cpp
    display/KwAbstractLayer.cpp
    display/KwImageLayer.cpp
    display/KwVideoLayer.cpp
    display/KwImageWidget.cpp
    display/KwTextLayer.cpp
    display/KwDisplayManager.cpp
    display/KwAbstractDisplayManager.cpp
    display/KwBackgroundManager.cpp
    display/KwTextManager.cpp
    display/KwOverlayManager.cpp
    display/KwDisplayStyles.cpp
)
set(kworshipmedia_SRCS
    media/KwMediaManager.cpp
    media/KwMediaPreferencesSequence.cpp
    media/KwMediaPreferencesAudio.cpp
    media/KwMediaControlWidget.cpp
    media/KwMediaControlWidgetAudio.cpp
    media/KwMediaControlWidgetSequence.cpp
    media/KwMediaControlWidgetVisual.cpp
    media/KwAbstractMediaPreferences.cpp
    media/KwMediaPreferencesVisual.cpp
    media/KwMediaItem.cpp
)
set(kworshipplaylist_SRCS
    playlist/KwPlaylistNode.cpp
    playlist/KwPlaylistModel.cpp
    playlist/KwPlaylistFile.cpp
    playlist/KwPlaylistFileNode.cpp
    playlist/KwPlaylistImage.cpp
    playlist/KwPlaylistVideo.cpp
    playlist/KwPlaylistItem.cpp
    playlist/KwPlaylistUnknown.cpp
    playlist/KwPlaylistUnknownNode.cpp
    playlist/KwPlaylistPaged.cpp
    playlist/KwPlaylistPagedNode.cpp
    playlist/KwPlaylistPagedNodePage.cpp
    playlist/KwPlaylistList.cpp
    playlist/KwPlaylistListNode.cpp
    playlist/KwPlaylistNote.cpp
    playlist/KwPlaylistNoteNode.cpp
    playlist/KwPlaylistPresentation.cpp
    playlist/KwPlaylistText.cpp
    playlist/KwPlaylistTextNode.cpp
)

set(kworshipmain_SRCS
    main.cpp
    KwApplication.cpp
    kworship.cpp
    kworshipview.cpp
    prefsDisplay.cpp
    prefsDatabase.cpp
    DesktopView.cpp
    KwDatabaseSetup.cpp
    KwDocument.cpp
    KwPlugin.cpp
    KwPluginManager.cpp
    ${kworshiparchive_SRCS}
    ${kworshipcss_SRCS}
    ${kworshipdisplay_SRCS}
    ${kworshipmedia_SRCS}
    ${kworshipplaylist_SRCS}
)

kde4_add_ui_files(kworshipmain_SRCS
                  kworshipview_base.ui
                  prefs_base.ui
                  prefsDisplay_base.ui
                  prefsDatabase_base.ui
                  prefsPresentations_base.ui
)

kde4_add_kcfg_files(kworshipmain_SRCS settings.kcfgc )

# Shared library with everything in
kde4_add_library(kworshipmain SHARED ${kworshipmain_SRCS})
target_link_libraries(kworshipmain
                      ${KDE4_KDEUI_LIBS}
                      ${KDE4_KIO_LIBS}
                      ${KDE4_KHTML_LIBS}
                      ${QT_LIBRARIES}
                      ${PHONON_LIBS}
                      unipresent
                      kworshipsongdb
)

set(kworship_SRCS
    kworshipexe.cpp
)
kde4_add_executable(kworship ${kworship_SRCS})
target_link_libraries(kworship kworshipmain)

########### install files ###############

install(TARGETS kworshipmain DESTINATION ${LIB_INSTALL_DIR} )
install(TARGETS kworship DESTINATION ${BIN_INSTALL_DIR} )

install( FILES kworship.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES kworship.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES kworshipui.rc  DESTINATION  ${DATA_INSTALL_DIR}/kworship )
install( FILES kworship_plugin.desktop  DESTINATION  ${SERVICETYPES_INSTALL_DIR} )

