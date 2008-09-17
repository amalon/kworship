project(kworshipsongdb)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworshipsongdb_MOC_SRCS
)
set(kworshipsongdb_SRCS
    KwSongdb.cpp
    KwSongdbModel.cpp
    KwSongdbNode.cpp
    KwSongdbFilterNode.cpp
    KwSongdbVersionNode.cpp
    ${kworshipsongdb_MOC_SRCS}
)

kde4_add_ui_files(kworshipsongdb_MOC_SRCS)

kde4_add_library(kworshipsongdb ${kworshipsongdb_SRCS})

