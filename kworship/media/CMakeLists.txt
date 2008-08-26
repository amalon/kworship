project(kworshipmedia)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworshipmedia_MOC_SRCS
)
set(kworshipmedia_SRCS
    KwMediaControlWidgetAudio.cpp
    KwMediaControlWidget.cpp
    KwMediaControlWidgetSequence.cpp
    KwMediaControlWidgetVisual.cpp
    KwMediaManager.cpp
    KwAbstractMediaPreferences.cpp
    KwMediaPreferencesAudio.cpp
    KwMediaPreferencesSequence.cpp
    KwMediaPreferencesVisual.cpp
    KwMediaItem.cpp
    ${kworshipmedia_MOC_SRCS}
)

kde4_add_ui_files(kworshipmedia_MOC_SRCS)

kde4_add_library(kworshipmedia ${kworshipmedia_SRCS})

