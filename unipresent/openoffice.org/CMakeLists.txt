project(unipresentopenoffice)

set(SHOULD_BUILD_OOO_PLUGIN NO)
if (NOT SHOULD_BUILD_OOO_PLUGIN)
  message(STATUS "OpenOffice.org Impress integration plugin will not be built")
else (NOT SHOULD_BUILD_OOO_PLUGIN)

  # We need uno
  find_package(UNO)
  if (NOT UNO_FOUND)
    message(STATUS "OpenOffice.org SDK NOT found - OpenOffice.org Impress integration plugin will not be built")
  else (NOT UNO_FOUND)
    message(STATUS "OpenOffice.org SDK found - OpenOffice.org Impress integration plugin will be built")

    find_package(KDE4 REQUIRED)

    # Remove flags from CMAKE_CXX_FLAGS
    MACRO (REMOVE_CXX_FLAGS)
      FOREACH(FLAG ${ARGN})
        STRING(REPLACE "${FLAG}" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
      ENDFOREACH(FLAG)
    ENDMACRO (REMOVE_CXX_FLAGS)

    # KDE adds a bunch of flags, several of which UNO doesn't like
    # UNO throws exceptions
    REMOVE_CXX_FLAGS(-fno-exceptions)
    # -fvisibility=hidden prevents us from catching UNO exceptions
    REMOVE_CXX_FLAGS(-fvisibility=hidden)
    # These flags cause lots of warnings with UNO
    REMOVE_CXX_FLAGS(-Wnon-virtual-dtor -Wundef -Wall -Wformat-security)

    include_directories(${KDE4_INCLUDES}
                        ${QT_INCLUDES})

    include_directories(${UNO_INCLUDES})

    set(unipresentopenoffice_UNOTYPES
        com.sun.star.beans.XPropertySet
        com.sun.star.bridge.XUnoUrlResolver
        com.sun.star.container.XEnumeration
        com.sun.star.container.XEnumerationAccess
        com.sun.star.container.XIndexAccess
        com.sun.star.container.XHierarchicalNameAccess
        com.sun.star.drawing.XDrawPagesSupplier
        com.sun.star.drawing.XDrawPages
        com.sun.star.drawing.XDrawPage
        com.sun.star.drawing.XShapes
        com.sun.star.text.XText
        com.sun.star.frame.XComponentLoader
        com.sun.star.frame.XDesktop
        com.sun.star.lang.XComponent
        com.sun.star.lang.XMultiComponentFactory
        com.sun.star.lang.XMultiServiceFactory
        com.sun.star.presentation.XPresentationSupplier
        com.sun.star.presentation.XPresentation
        com.sun.star.registry.XSimpleRegistry
    )

    set(unipresentopenoffice_SRCS
        UpOoBackend.cpp
        UpOoBridge.cpp
        UpOoPresentation.cpp
        UpOoSlide.cpp
    )

    UNO_ADD_TYPES(unipresentopenoffice_SRCS
                  ${unipresentopenoffice_UNOTYPES}
    )

    kde4_add_library(unipresentopenoffice STATIC ${unipresentopenoffice_SRCS})

    target_link_libraries(unipresentopenoffice
                          ${UNO_LIBS}
    )

    ########### install files ###############

    install( FILES ${UNO_RDB}
             DESTINATION  ${DATA_INSTALL_DIR}/unipresent/openoffice.org
             RENAME "types.rdb" )
  endif (NOT UNO_FOUND)
endif (NOT SHOULD_BUILD_OOO_PLUGIN)
