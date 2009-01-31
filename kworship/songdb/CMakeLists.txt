project(kworship_songdb)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworship_songdb_SRCS
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
)

kde4_add_ui_files(kworship_songdb_SRCS
                  KwSongdbSongEditWidget_base.ui
                  KwSongdbSongBooksEditWidget_base.ui
)

kde4_add_library(kworship_songdb SHARED ${kworship_songdb_SRCS})

target_link_libraries(kworship_songdb
                      ${KDE4_KDEUI_LIBS}
                      ${QT_LIBRARIES}
                      kworshipmain
                      )
