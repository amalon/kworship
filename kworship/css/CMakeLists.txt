project(kworshipcss)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworshipcss_MOC_SRCS
)
set(kworshipcss_SRCS
    KwCssAbstractStyle.cpp
    KwCssAbstractStyleState.cpp
    KwCssScope.cpp
    KwCssScopeKey.cpp
    KwCssStyles.cpp
    KwCssStyleStates.cpp
    KwCssStyleRule.cpp
    KwCssStyleSheet.cpp
    KwCssStyleSheetFile.cpp
    ${kworshipcss_MOC_SRCS}
)

kde4_add_ui_files(kworshipcss_MOC_SRCS)

kde4_add_library(kworshipcss ${kworshipcss_SRCS})

