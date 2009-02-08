project(kworship_songdb)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworship_songdb_SRCS
    KwSongdbPlugin.cpp
    KwSongdb.cpp
    KwSongdbSong.cpp
    KwSongdbVersion.cpp
    KwSongdbSongBook.cpp
    KwSongdbSongBookSong.cpp
    KwSongdbLyrics.cpp
    KwSongdbLyricsLayout.cpp
    KwSongdbModel.cpp
    KwSongdbNode.cpp
    KwSongdbFilterNode.cpp
    KwSongdbVersionNode.cpp
    # User interface
    KwSongdbTree.cpp
    KwSongdbTreeGroupAction.cpp
    KwSongdbVersionItem.cpp
    KwSongdbSongEditWidget.cpp
    KwSongdbSongEditDialog.cpp
    KwSongdbSongBookItem.cpp
    KwSongdbSongBookSongItem.cpp
    KwSongdbSongBooksEditWidget.cpp
    # Playlist
    KwPlaylistSong.cpp
    KwPlaylistSongNode.cpp
    KwPlaylistSongNodeVerse.cpp
)

include_directories(..)

kde4_add_ui_files(kworship_songdb_SRCS
                  KwSongdbSongEditWidget_base.ui
                  KwSongdbSongBooksEditWidget_base.ui
)

kde4_add_plugin(kworship_songdb ${kworship_songdb_SRCS})

target_link_libraries(kworship_songdb
                      ${KDE4_KPARTS_LIBS}
                      ${KDE4_KDEUI_LIBS}
                      ${QT_LIBRARIES}
                      kworshipmain
                      )

install( TARGETS kworship_songdb DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES kworship_songdb.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )
install( FILES kworship_songdbui.rc  DESTINATION ${DATA_INSTALL_DIR}/kworship/songdb )
