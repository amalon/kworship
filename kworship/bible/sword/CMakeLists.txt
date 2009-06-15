project(kworship_bible_sword)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
find_package(Sword)

if(NOT SWORD_FOUND)
    message(STATUS "Sword plugin will not be built")
else(NOT SWORD_FOUND)

set(kworship_bible_sword_SRCS
    KwBibleManagerSword.cpp
    KwBibleModuleSword.cpp
)

include_directories(${SWORD_INCLUDE_DIR}
                    ..)

kde4_add_plugin(kworship_bible_sword ${kworship_bible_sword_SRCS})

target_link_libraries(kworship_bible_sword
                      kworship_bible
                      ${KDE4_KDECORE_LIBS}
                      ${QT_LIBRARIES}
                      ${SWORD_LIBS}
                      )

install( TARGETS kworship_bible_sword DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES kworship_bible_sword.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )

endif(NOT SWORD_FOUND)
