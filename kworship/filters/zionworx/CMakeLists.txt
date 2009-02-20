project(kworship_zionworx)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(kworship_zionworx_SRCS
    KwZionworxPlugin.cpp
    KwZionworxFilter.cpp
    KwPascalStream.cpp
)

include_directories(../.. ../../playlist ../../bible)
add_subdirectory(mimetypes)

kde4_add_plugin(kworship_zionworx ${kworship_zionworx_SRCS})

target_link_libraries(kworship_zionworx
                      ${KDE4_KPARTS_LIBS}
                      ${QT_LIBRARIES}
                      kworshipmain
                      kworship_bible
                      kworship_songdb
                      )

install( TARGETS kworship_zionworx DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES kworship_zionworx.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )
