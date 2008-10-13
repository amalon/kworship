project(kworshiparchive)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworshiparchive_SRCS
    KwResourceLink.cpp
    KwResourceManager.cpp
    KwDataFile.cpp
    KwArchive.cpp
)

kde4_add_library(kworshiparchive ${kworshiparchive_SRCS})

