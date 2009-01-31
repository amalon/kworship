project(kworship_bible_biblegateway)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
find_package(Sword REQUIRED)

set(kworship_bible_biblegateway_SRCS
    KwBibleManagerBibleGateway.cpp
    KwBibleModuleBibleGateway.cpp
)

include_directories(${SWORD_INCLUDE_DIR}
                    ..)

kde4_add_plugin(kworship_bible_biblegateway ${kworship_bible_biblegateway_SRCS})

target_link_libraries(kworship_bible_biblegateway
                      kworship_bible
                      ${KDE4_KDECORE_LIBS}
                      ${QT_LIBRARIES}
                      )

install( TARGETS kworship_bible_biblegateway DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES kworship_bible_biblegateway.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )
