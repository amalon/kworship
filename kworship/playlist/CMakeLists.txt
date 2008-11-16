project(kworshipplaylist)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworshipplaylist_SRCS
    KwPlaylistNode.cpp
    KwPlaylistModel.cpp
    KwPlaylistFile.cpp
    KwPlaylistFileNode.cpp
    KwPlaylistImage.cpp
    KwPlaylistVideo.cpp
    KwPlaylistItem.cpp
    KwPlaylistUnknown.cpp
    KwPlaylistUnknownNode.cpp
    KwPlaylistPaged.cpp
    KwPlaylistPagedNode.cpp
    KwPlaylistPagedNodePage.cpp
    KwPlaylistList.cpp
    KwPlaylistListNode.cpp
    KwPlaylistNote.cpp
    KwPlaylistNoteNode.cpp
    KwPlaylistPresentation.cpp
    KwPlaylistSong.cpp
    KwPlaylistSongNode.cpp
    KwPlaylistSongNodeVerse.cpp
    KwPlaylistText.cpp
    KwPlaylistTextNode.cpp
)

kde4_add_library(kworshipplaylist ${kworshipplaylist_SRCS})

target_link_libraries(kworshipplaylist
                      kworshiparchive
)
