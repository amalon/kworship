project(kworshipsongdb)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworshipsongdb_SRCS
    KwSongdb.cpp
    KwSongdbSong.cpp
    KwSongdbVersion.cpp
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
    KwSongdbSongBooksEditWidget.cpp
)

kde4_add_ui_files(kworshipsongdb_SRCS
                  KwSongdbSongEditWidget_base.ui
                  KwSongdbSongBooksEditWidget_base.ui
)

kde4_add_library(kworshipsongdb ${kworshipsongdb_SRCS})

