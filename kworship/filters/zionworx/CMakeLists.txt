project(kworship_zionworx)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
set(QT_USE_QTSQL 1)
include(${QT_USE_FILE})
include_directories(${KDE4_INCLUDES}
                    ${QT_INCLUDES}
)

set(kworship_zionworx_SRCS
    main.cpp
    KwZwStringList.cpp
)
kde4_add_executable(kworship_zionworx ${kworship_zionworx_SRCS})
target_link_libraries(kworship_zionworx
                      ${KDE4_KDEUI_LIBS}
                      ${QT_LIBRARIES}
)
