project(kworshipcss)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworshipcss_SRCS
    KwCssAbstractStyle.cpp
    KwCssAbstractStyleState.cpp
    KwCssScope.cpp
    KwCssScopeKey.cpp
    KwCssStyles.cpp
    KwCssStyle.cpp
    KwCssStyleStates.cpp
    KwCssStyleRule.cpp
    KwCssStyleSheet.cpp
    KwCssStyleSheetFile.cpp
)

kde4_add_library(kworshipcss ${kworshipcss_SRCS})

