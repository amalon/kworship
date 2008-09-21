project(kworshipmedia)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworshipmedia_SRCS
    KwMediaManager.cpp
    KwMediaPreferencesSequence.cpp
    KwMediaPreferencesAudio.cpp
    KwMediaControlWidget.cpp
    KwMediaControlWidgetAudio.cpp
    KwMediaControlWidgetSequence.cpp
    KwMediaControlWidgetVisual.cpp
    KwAbstractMediaPreferences.cpp
    KwMediaPreferencesVisual.cpp
    KwMediaItem.cpp
)

kde4_add_library(kworshipmedia ${kworshipmedia_SRCS})

