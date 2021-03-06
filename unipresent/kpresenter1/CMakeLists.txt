# Don't bother if kpresenter 1 doesn't run on the target system
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(ENABLE_UNIPRESENT_KPRESENTER1 true)
  message(STATUS "KPresenter 1 integration plugin will be built")
else(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message(STATUS "Non-Linux target - KPresenter 1 integration plugin will not be built")
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")

if(ENABLE_UNIPRESENT_KPRESENTER1)
  project(unipresent_kpresenter1)

  find_package(KDE4 REQUIRED)
  include (KDE4Defaults)
  include_directories(${KDE4_INCLUDES}
                      ${QT_INCLUDES}
  )

  set(unipresent_kpresenter1_SRCS
      UpKpr1Dcop.cpp
      UpKpr1AppsDcop.cpp
      UpKpr1KpresenterDcop.cpp
      UpKpr1Backend.cpp
      UpKpr1Presentation.cpp
      UpKpr1PresentationDcop.cpp
      UpKpr1ViewDcop.cpp
      UpKpr1Slide.cpp
      UpKpr1SlideDcop.cpp
  )

  kde4_add_plugin(unipresent_kpresenter1 ${unipresent_kpresenter1_SRCS})

  target_link_libraries(unipresent_kpresenter1
                        unipresent
                        ${KDE4_KDEUI_LIBS}
                        ${QT_LIBRARIES}
                        )

  install( TARGETS unipresent_kpresenter1 DESTINATION ${PLUGIN_INSTALL_DIR} )
  install( FILES unipresent_kpresenter1.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )
endif(ENABLE_UNIPRESENT_KPRESENTER1)
