project(kworship_bible)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworship_bible_SRCS
    KwBiblePlugin.cpp
    KwBibleManager.cpp
    KwBibleModule.cpp
    KwBiblePassage.cpp
    KwBiblePlaylistItem.cpp
    KwBiblePlaylistItemNode.cpp
)

add_subdirectory (sword)
add_subdirectory (biblegateway)

include_directories(${SWORD_INCLUDE_DIR}
                    ..)

kde4_add_plugin(kworship_bible ${kworship_bible_SRCS})

target_link_libraries(kworship_bible
                      ${KDE4_KDECORE_LIBS}
                      ${KDE4_KHTML_LIBS}
                      ${QT_LIBRARIES}
                      ${SWORD_LIBS}
                      kworshipmain
                      )

install( TARGETS kworship_bible DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES kworship_bible.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )
install( FILES kworship_bibleui.rc  DESTINATION
${DATA_INSTALL_DIR}/kworship/bible )
install( FILES kworship_bible_backend.desktop  DESTINATION  ${SERVICETYPES_INSTALL_DIR} )
