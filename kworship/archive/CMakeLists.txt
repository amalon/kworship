project(kworshiparchive)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworshiparchive_SRCS
    KwArchive.cpp
    KwDataFile.cpp
)

kde4_add_library(kworshiparchive ${kworshiparchive_SRCS})

