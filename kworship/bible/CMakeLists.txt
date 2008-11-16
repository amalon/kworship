project(kworshipbible)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
find_package(Sword REQUIRED)

set(kworshipbible_SRCS
    KwBibleManager.cpp
    KwBibleModule.cpp
    KwBiblePlaylistItem.cpp
    KwBiblePlaylistItemNode.cpp
    # SWORD
    KwBibleManagerSword.cpp
    KwBibleModuleSword.cpp
    # BibleGateway.com
    KwBibleManagerBibleGateway.cpp
    KwBibleModuleBibleGateway.cpp
)

include_directories(${SWORD_INCLUDE_DIR})

kde4_add_library(kworshipbible ${kworshipbible_SRCS})

