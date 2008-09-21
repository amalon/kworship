project(kworshipsongdb)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworshipsongdb_SRCS
    KwSongdb.cpp
    KwSongdbSong.cpp
    KwSongdbVersion.cpp
    KwSongdbLyrics.cpp
    KwSongdbLyricsOrder.cpp
    KwSongdbTree.cpp
    KwSongdbTreeGroupAction.cpp
    KwSongdbModel.cpp
    KwSongdbNode.cpp
    KwSongdbFilterNode.cpp
    KwSongdbVersionNode.cpp
)

kde4_add_library(kworshipsongdb ${kworshipsongdb_SRCS})

